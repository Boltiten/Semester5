import torch
import numpy as np

print(np.array([[1,2],[3,4]]))

print(torch.tensor([[1,2],[3,4]]))

print(np.array([[1,2],[3,4]]) @np.array([[1,2],[3,4]]))

print(torch.tensor([[1,2],[3,4]]) @torch.tensor([[1,2],[3,4]]))