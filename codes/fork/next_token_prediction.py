import torch
import torch.nn.functional as F
from transformers import LlamaModel, LlamaConfig, LlamaForCausalLM


# 加载模型
config=  LlamaConfig(vocab_size = 100,
                     hidden_size = 256,
                     intermedidate_size=512,
                     num_hidden_layers= 2,
                     num_attention_heads= 4,
                     num_key_values_heads =  4,
                     )

model = LlamaForCausalLM(config)


# 创建数据、不使用tokenizer
X = torch.randint(0, 100, (1,10))
print(X.shape)


# 
idx={}
idx['input_ids'] = X
for i in range(4):
    print(f"\nGeneration第{i}个时的输入{idx['input_ids'].shape}：")
    print(f"Generation第{i}个时的输入{idx['input_ids']}：")
    output = model(**idx) 
    logits = output['logits'][:,-1,:]
    idx_next = torch.argmax(logits , dim=1)[0]
    idx['input_ids'] = torch.cat((idx['input_ids'], idx_next.unsqueeze(0).unsqueeze(1)), dim=-1) 

