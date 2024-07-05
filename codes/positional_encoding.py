import torch
import torch.nn as nn
import torch.nn.functional as F


def creat_1d_absolute_sincos_embedings(n_pos_vec, n_, dim):
	# n_pos_vec torch.arange(max_seq_len)
	n_pos_vec = torch.arange(max_seq_len)

	assert dim % 2 == 0, "wrong dimension"
	position_embedding = torch.zeros(n_pos_vec.nueml(), dim)

    # 对i进行一个遍历（0，d/model)
	omega = torch.arange(dim//2, dtype=torch.float)
	omega /=  dim/2
	omege = 1. / (10000** omega)

	out = n_pos_vec[:,None] @ omega[None,:]
	emb_sin = torch.sin(out)
	emb_cos = torch.cos(out)

    # 偶数位置
    # 奇数位置
	position_embedding[:, 0::2] = embed_sin
	position_embedding[:, 1::2] = embed_cos


def creat_1d_absolute_trainable_embeddings(n_pos_vec, dim):
	postion_embedding = nn.Embedding(n_pos_vec.nueml(),dim)
	# 初始化的是参数矩阵
	nn.init.constant(position_embedding.weight,0)
	return postion_embedding

# 3. 2d relative bias trainable embeddings
#  swing transformer
def 


# 4. 2d_absolute_sincos_embeddings
# mae kaiming he
def 


if __name__ == "__main__":
	n_pos = 4
	dim = 4
	n_pos_vec = torch.arange(n_pos, dtype=torch.float)
	pe = creat_1d_absolute_sincos_embedings(n_pos_vec, dim)










