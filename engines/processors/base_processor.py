#!/usr/bin/env python
# -*-coding:utf-8 -*-
#'''
#@File    :   base_processor.py
#@Time    :   2024/06/07 12:25:16
#@Author  :   Daoming Zong and Chunya Liu
#@Version :   1.0
#@Contact :   zongdaoming@sensetime.com
#@License :   (C)Copyright 2022-2023, SenseTime Research
#@Desc    :   None
#'''

from omegaconf import OmegaConf


class BaseProcessor:
    def __init__(self):
        self.transform = lambda x: x
        return

    def __call__(self, item):
        return self.transform(item)

    @classmethod
    def from_config(cls, cfg=None):
        return cls()

    def build(self, **kwargs):
        cfg = OmegaConf.create(kwargs)

        return self.from_config(cfg)
