#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np


def add123(arr):
    print "In python: " + str(arr)
    assert len(arr.shape) == 1, 'Array must be 1-d dimensional'
    assert arr.shape[0] == 3, 'Shape of array must be (3,)'
    return arr + np.array([1, 2, 3])


if __name__ == '__main__':
    pass
