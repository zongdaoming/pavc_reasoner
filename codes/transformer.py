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
        self.embeddings = nn.Embedding(num_embeddings=self.vocab_size, embedding_dim=self.hidden_dim)
        self.positional_encoding = self._generate_positional_encoding(max_length=self.max_length, dim=self.word_embedding_dim)
        ##############################################################################

        ##############################################################################
        # Deliverable 2: Initializations for multi-head self-attention.
        self.Wq = nn.Linear(self.hidden_dim, self.hidden_dim, bias=False)
        self.Wk = nn.Linear(self.hidden_dim, self.dim_k * self.num_heads, bias=False)
        self.Wv = nn.Linear(self.hidden_dim, self.dim_v * self.num_heads, bias=False)
        self.Wo = nn.Linear(self.hidden_dim, self.hidden_dim, bias=False)
        ##############################################################################

        ##############################################################################
        # Deliverable 3: Initialize what you need for the feed-forward layer.
        self.feed_forward = nn.Sequential(
            nn.Linear(self.hidden_dim, self.dim_feedforward),
            nn.ReLU(),
            nn.Linear(self.dim_feedforward, self.hidden_dim)
        )
        ##############################################################################

        ##############################################################################
        # Deliverable 4: Initialize what you need for the final layer.
        self.final_layer = nn.Linear(self.hidden_dim, 1)
        ##############################################################################

    # ... (rest of the class definition)
    
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
        outputs = nn.LayerNorm(outputs)(outputs)  # Apply layer normalization

        # Apply the feed-forward layer and add residual connection
        ff_output = self.feedforward_layer(outputs)
        outputs = outputs + ff_output
        outputs = nn.LayerNorm(outputs)(outputs)  # Apply layer normalization

        # Apply the final layer to get the binary classification score
        final_output = self.final_layer(outputs)

        return final_output
    
    
    def _generate_positional_encoding(self, max_length, dim, min_timescale=1.0, max_timescale=10000.0):
        """
        Generate positional encoding as per Attention is All You Need paper.
        """
        pe = torch.zeros(max_length, dim)
        position = torch.arange(0, max_length, dtype=torch.float).unsqueeze(1)
        div_term = torch.exp(torch.arange(0, dim, 2).float() * (-math.log(10000.0) / dim))
        pe[:, 0::2] = torch.sin(position * div_term)
        pe[:, 1::2] = torch.cos(position * div_term)
        pe = pe.unsqueeze(0).transpose(0, 1)
        return pe

    def embed(self, inputs):
        """
        Embed the input tokens and add positional encoding.
        """
        embeddings = self.embeddings(inputs) * math.sqrt(self.word_embedding_dim)
        embeddings = embeddings + self.positional_encoding[:inputs.size(1), :]
        return embeddings

    def multi_head_attention(self, inputs, mask):
        """
        Implement multi-head self-attention.
        """
        batch_size, seq_length, dim = inputs.size()
        q = self.W_q(inputs).view(batch_size, seq_length, self.num_heads, -1)
        k = self.W_k(inputs).view(batch_size, seq_length, self.num_heads, -1)
        v = self.W_v(inputs).view(batch_size, seq_length, self.num_heads, -1)
        # 需要转置
        scores = torch.einsum("bnqd,bnkd->bnqk", q, k) / torch.sqrt(torch.tensor(dim, dtype=torch.float32))
        if mask is not None:
            scores = scores.masked_fill(mask == 0, float("-1e20"))
        attention = torch.softmax(scores, dim=-1)
        # 不需要转置
        output = torch.einsum("bnqk,bnkd->bnqd", attention, v).contiguous()
        output = output.view(batch_size, seq_length, -1)
        return self.out_layer(output)

    def feedforward_layer(self, inputs):
        """
        Implement the feedforward layer.
        """
        return self.feed_forward(inputs)

    def final_layer(self, inputs):
        """
        Implement the final layer for the Transformer classifier.
        """
        return torch.sigmoid(self.final_layer(inputs))

    # ... (rest of the class definition)

def seed_torch(seed=0):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.backends.cudnn.benchmark = False
    torch.backends.cudnn.deterministic = True

