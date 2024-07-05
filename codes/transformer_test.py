import numpy as np
import torch
from torch import nn
import random
import math

class ClassificationTransformer(nn.Module):
    def __init__(self, word_to_ix, hidden_dim=128, num_heads=2, dim_feedforward=2048, dim_k=96, dim_v=96, dim_q=96, max_length=43):
    	super(ClassificationTransformer, self).__init__()
    	assert hidden_dim % num_heads == 0
    	self.num_heads = num_heads
    	self.word_embedding_dim =  hidden_dim 
    	self.hidden_dim = hidden_dim 
    	self.dim_feedforward = dim_feedforward
    	self.max_length = max_length
    	self.vocab_size = len(word_to_ix)
    	self.dim_k = dim_k 
    	self.dim_v = dim_v 
    	self.dim_q = dim_q 

    	# deliverable
    	# 词表的最大长度
    	self.embeddings = nn.Embedding(self.vocab_size, self.word_embedding_dim)
    	# 单词的最大长度
    	# self.positional_embedding = nn.Embedding(self.max_length, self.word_embedding_dim)
    	self.positional_embedding = self._generate_positional_encoding(self.max_length, self.word_embedding_dim)

    	# define q,k,v
    	# in most cases, hidden_dim % num_heads == 0
    	self.W_q = nn.Linear(self.hidden_dim, self.dim_q*self.num_heads, bias=False)
    	self.W_k = nn.Linear(self.hidden_dim, self.dim_k*self.num_heads, bias=False)
    	self.W_v = nn.Linear(self.hidden_dim, self.dim_v*self.num_heads, bias=False)
    	self.W_o = nn.Linear(self.dim_v*self.num_heads, self.hidden_dim, bias=False)
    	self.norm1 = nn.LayerNorm(hidden_dim)
    	self.norm2 = nn.LayerNorm(hidden_dim)
    	# deliverable
    	self.ffn_layer = nn.Sequential(
    		nn.Linear(self.hidden_dim, self.dim_feedforward),
    		nn.ReLU(),
    		nn.Linear(self.dim_feedforward, self.hidden_dim),
    		)
    	# deliverable
    	self.final_layer = nn.Linear(self.hidden_dim, 1)

    def _generate_positional_encoding(self,max_length,dim):
    	pe = torch.zeros(max_length,dim)
    	position =  torch.arange(0, max_length, dtype=torch.float32).unsqueeze(1)
    	div_term = torch.exp(torch.arange(0,dim,2).float()*(-math.log(10000.0)/dim))
    	pe[:,0::2] = torch.sin(position * div_term)
    	pe[:,1::2] = torch.cos(position * div_term)
    	return pe

    def _generate_positional_encoding2(self, max_length, dim):
    	pe = torch.zeros(max_length， dim)
    	for pos in range(max_length):
    		for i in range(0, dim, 2)：
    		pe[pos, i] = torch.sin(pos/(10000**((2*i)/dim)))
    		pe[pos, i+1] = torch.cos(pos/(10000**(2*i)/dim))
    	return pe

    def embed(self, inputs):
    	embeddings = self.embeddings(inputs)
    	embeddings =  embeddings + self.positional_embedding[:inputs.size(1),:]
    	return embeddings

    def multi_head_attention(self,inputs):
    	batch_size, seq_len, hidden_dim = inputs.shape
    	Q = self.Wq(inputs).view(batch_size, seq_len, self.num_heads, self.dim_q)
    	K = self.Wk(inputs).view(batch_size, seq_len, self.num_heads, self.dim_k)
    	V = self.Wv(inputs).view(batch_size, seq_len, self.num_heads, self.dim_v)
    	# compute attention scores
    	# query,key 的维度是一样的
    	scores = torch.matmul(Q,K.transpose(-2, -1)) / math.sqrt(self.dim_k)
    	scores = torch.softmax(scores, dim=-1)
    	# compute attention output
    	attention_output = torch.matmul(scores, V)
    	attention_output = attention_output.view(batch_size, seq_len, self.dim_v*self.num_heads)
    	output = self.W_o(attention_output)
    	return output

    def forward(self, inputs):
    	# embed the input tokens and add positional encoding
    	embeddings =  self.embed(inputs)
    	# Initialize the output with the embedded input
    	outputs = embeddings
    	
    	# Apply multi-head self-attention and add residual connection
    	attention_output = self.multi_head_attention(outputs)
    	outputs = outputs + attention_output
    	outputs = self.norm1(outputs) # post norm

    	# Apply the feed-forward layer and add residual connection
    	ffn_output = self.ffn_layer(outputs)
    	outputs = outputs + ffn_output
    	outputs = self.norm2(outputs) # post norm

    	# Apply the final layer to get the binary classification score
    	final_output = self.final_layer(outputs)
    	return final_output



































	









