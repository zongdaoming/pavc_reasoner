# transformer
import numpy as np
import torch
from torch import nn
import random
import math
class ClassificationTransformer(nn.Module):
    """
    A single-layer Transformer which encodes a sequence of text and
    performs binary classification.
    The model has a vocab size of V, works on
    sequences of length T, has an hidden dimension of H, uses word vectors
    also of dimension H, and operates on minibatches of size N.
    """
    def __init__(self, word_to_ix, hidden_dim=128, num_heads=2, dim_feedforward=2048, dim_k=96, dim_v=96, dim_q=96, max_length=43):
        '''
        :param word_to_ix: dictionary mapping words to unique indices
        :param hidden_dim: the dimensionality of the output embeddings that go into the final layer
        :param num_heads: the number of Transformer heads to use
        :param dim_feedforward: the dimension of the feedforward network model
        :param dim_k: the dimensionality of the key vectors
        :param dim_q: the dimensionality of the query vectors
        :param dim_v: the dimensionality of the value vectors
        '''
        super(ClassificationTransformer, self).__init__()
        assert hidden_dim % num_heads == 0
        self.num_heads = num_heads
        self.word_embedding_dim = hidden_dim
        self.hidden_dim = hidden_dim
        self.dim_feedforward = dim_feedforward
        self.max_length = max_length
        self.vocab_size = len(word_to_ix)
        self.dim_k = dim_k
        self.dim_v = dim_v
        self.dim_q = dim_q
        seed_torch(0)
        
        ##############################################################################
        # Deliverable 1: Initialize what you need for the embedding lookup.
        self.embeddings = nn.Embedding(self.vocab_size, self.word_embedding_dim)
        self.postional_encoding = self._generate_positional_encoding(max_length=self.max_length, dim = self.word_embedding_dim)
        # self.postional_encoding = nn.Embedding(self.max_length, self.word_embedding_dim)
        ##############################################################################
        # Deliverable 2: Initializations for multi-head self-attention.
        self.Wq = nn.Linear(self.hidden_dim, self.dim_q*self.num_heads, bias=False)
        self.Wk = nn.Linear(self.hidden_dim, self.dim_k*self.num_heads, bias=False)
        self.Wv = nn.Linear(self.hidden_dim, self.dim_v*self.num_heads, bias=False)
        self.Wo = nn.Linear(self.dim_v*self.num_heads, self.hidden_dim, bias=False)
        self.norm1 = nn.LayerNorm(hidden_dim)
        self.norm2 = nn.LayerNorm(hidden_dim)
        ##############################################################################
        # Deliverable 3: Initialize what you need for the feed-forward layer.
        self.feed_word = nn.Sequential(
            nn.Linear(self.hidden_dim, self.dim_feedforward),
            nn.ReLU(),
            nn.Linear(self.dim_feedforward, self.hidden_dim),
        )
        ##############################################################################
        ##############################################################################
        # Deliverable 4: Initialize what you need for the final layer.
        self.final_layer = nn.Linear(self.hidden_dim, 1)  
      
    def _generate_positional_encoding(self, max_length, dim):
        '''
        Generates a Pytorch tensor of size (max_length, dim)
        containing the positional encodings for
        max_length and dim dimensions.
        '''
        pe = torch.zeros(max_length, dim)
        position = torch.arange(0, max_length, dtype=torch.float).unsqueeze(1)
        # div_term = torch.exp(torch.arange(0,  dim,  2).float() * (-math.log(10000.0) / dim))
        div_term = torch.exp(torch.arange(0,  dim,  2).float() * (-math.log(10000.0) / dim))
        pe[:, 0::2] = torch.sin(position * div_term)
        pe[:, 1::2] = torch.cos(position * div_term)
        return pe
    
        # self.positional_encoding = torch.zeros(self.max_length, self.hidden_dim)
        # for pos in range(self.max_length):
        #     for i in range(0, self.hidden_dim, 2):
        #         self.positional_encoding[pos, i] = torch.sin(pos / (10000 ** ((2 * i) / self.hidden_dim)))
        #         self.positional_encoding[pos, i + 1] = torch.cos(pos / (10000 ** ((2 * (i)) / self.hidden_dim)))
        # self.positional_encoding = self.positional_encoding.unsqueeze(0)
        
    def _generate_positional_encoding2(self, max_length, dim):
        pe = torch.zeros(max_length, dim)
        position = torch.arange(0, max_length, dtype=torch.float).unsqueeze(1)
        div_term = torch.exp(torch.arange(0, dim, 2).float() * (-math.log(10000.0) / dim))
        pe[:, 0::2] = torch.sin(position * div_term)
        pe[:, 1::2] = torch.cos(position * div_term)
        return pe
            
    def embed(self, inputs):
        """
        Embed the input tokens and add positional encoding.
        """
        embeddings = self.embeddings(inputs)
        embeddings = embeddings + self.postional_encoding[:inputs.size(1), :]
        return embeddings
    
    def multi_head_attention(self, inputs):
        '''
        Perform multi-head attention.
        '''
        # embeddings: (batch_size, seq_len, hidden_dim)
        batch_size, seq_len, hidden_dim =inputs.shape
        Q = self.Wq(inputs).view(batch_size, seq_len, self.num_heads, self.dim_q)    
        K = self.Wk(inputs).view(batch_size, seq_len, self.num_heads, self.dim_k)
        V = self.Wv(inputs).view(batch_size, seq_len, self.num_heads, self.dim_v)
        # compute attention scores
        scores = torch.matmul(Q, K.transpose(-2, -1)) / math.sqrt(self.dim_k)
        scores = torch.softmax(scores, dim=-1)
        # compute attention output
        attention_output = torch.matmul(scores, V)
        attention_output = attention_output.view(batch_size, seq_len, self.num_heads*self.dim_v)
        output = self.Wo(attention_output)
        return output
        

    def feed_forward(self, inputs):
        '''
        Perform feed-forward operation.
        '''
        return self.feed_word(inputs)
    def final_layer(self,inputs):
        '''
        Perform final layer operation.
        '''
        return self.final_layer(inputs)
    
    def forward(self, inputs):
        """
        This function computes the full Transformer forward pass.
        """
        # Embed the input tokens and add positional encoding
        embedded = self.embed(inputs)

        # Initialize the output with the embedded input
        outputs = embedded

        # Apply multi-head self-attention and add residual connection
        attention_output = self.multi_head_attention(outputs)
        outputs = outputs + attention_output
        outputs = nn.LayerNorm(outputs)(outputs)  # Apply layer normalization PostNorm

        # Apply the feed-forward layer and add residual connection
        ff_output = self.feedforward_layer(outputs)
        outputs = outputs + ff_output
        outputs = nn.LayerNorm(outputs)(outputs)  # Apply layer normalization PostNorm

        # Apply the final layer to get the binary classification score
        final_output = self.final_layer(outputs)
        return final_output