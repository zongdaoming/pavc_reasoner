# author: xiaodongguaAIGC
# KV-Cache + Generation + decoder 

import torch
import torch.nn.functional as F
from transformers import LlamaModel, LlamaConfig, LlamaForCausalLM

D = 128 # single-head-dim
V = 64  # vocab_size

class xiaodonggua_kv_cache(torch.nn.Module):
    def __init__(self, D, V):  
        super().__init__()
        self.D = D
        self.V = V
        self.Embedding = torch.nn.Embedding(V,D)
        self.Wq = torch.nn.Linear(D,D)     
        self.Wk = torch.nn.Linear(D,D)     
        self.Wv = torch.nn.Linear(D,D)
        self.lm_head = torch.nn.Linear(D,V) # LM_head
        self.cache_K = self.cache_V = None  # initial
        
    def forward(self,X):
        X = self.Embedding(X)
        Q,K,V = self.Wq(X),self.Wk(X),self.Wv(X)
        print("input_Q:", Q.shape)
        print("input_K:", K.shape)
        print("input_V:", V.shape)
        
        # Easy KV_Cache
        if self.cache_K == None:
            self.cache_K = K
            self.cache_V = V
        else:
            self.cache_K = torch.cat((self.cache_K, K), dim = 1)
            self.cache_V = torch.cat((self.cache_V, V), dim = 1)
            K = self.cache_K
            V = self.cache_V

        
        print("cache_K:", self.cache_K.shape)
        print("cache_V:", self.cache_K.shape)
        
        # ignore proj/MLP/scaled/mask/multi-head when calculate Attention
        attn =Q@K.transpose(1,2)@V
        
        # output
        output=self.lm_head(attn)
        return output

model = xiaodonggua_kv_cache(D,V)
        
# 创建数据、不使用tokenizer
X = torch.randint(0, 64, (1,10))
print(X.shape)

for i in range(4):
    print(f"\nGeneration {i} step input_shape: {X.shape}：")
    output = model.forward(X) 
    print(output.shape)
    next_token = torch.argmax(F.softmax(output, dim = -1),-1)[:,-1]
    print(next_token.shape)
    X = next_token.unsqueeze(0)
