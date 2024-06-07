#!/usr/bin/env python
# -*-coding:utf-8 -*-
#'''
#@File    :   __init__.py
#@Time    :   2024/06/07 12:25:42
#@Author  :   Daoming Zong and Chunya Liu
#@Version :   1.0
#@Contact :   zongdaoming@sensetime.com
#@License :   (C)Copyright 2022-2023, SenseTime Research
#@Desc    :   None
#'''
from pavc_reasoner.engines.processors.base_processor import BaseProcessor
from pavc_reasoner.engines.processors.blip_processors import (
    Blip2ImageTrainProcessor,
    Blip2ImageEvalProcessor,
    BlipCaptionProcessor,
)
from pavc_reasoner.engines.processors.video_processor import (
    AlproVideoTrainProcessor,
    AlproVideoEvalProcessor
)
from pavc_reasoner.utils.registry import registry

__all__ = [
    "BaseProcessor",
    "Blip2ImageTrainProcessor",
    "Blip2ImageEvalProcessor",
    "BlipCaptionProcessor",
    "AlproVideoTrainProcessor",
    "AlproVideoEvalProcessor",
]

def load_processor(name, cfg=None):
    """
    Example

    >>> processor = load_processor("alpro_video_train", cfg=None)
    """
    processor = registry.get_processor_class(name).from_config(cfg)

    return processor
