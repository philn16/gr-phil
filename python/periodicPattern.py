#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2018 Philip
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

import numpy
from gnuradio import gr

class periodicPattern(gr.sync_block):
	"""
	Documentation can be found in XML file
	"""
	def __init__(self, patternVector, type,debug):
		if debug:
			print("type is "+str(type))
		self.type={"float":numpy.float32,"complex":numpy.complex64}[type]
		gr.sync_block.__init__(self, name="periodicPattern", in_sig=None, out_sig=[(self.type,1)]) 
		self.patternVector=patternVector
		# duplicating the pattern vector can yield performance gains (if the vecotr is small)
		desiredListLen=2**12
		repetitions=(desiredListLen//len(self.patternVector))
		self.patternVector=numpy.array(list(self.patternVector)*repetitions,dtype=self.type)
		if debug:
			print("repeating pattern "+str(repetitions)+" times for performance")
		# For each work cycle, this is the first index to go to the output
		self.count=0

	def work(self, input_items, output_items):
		out = output_items[0]
		numOutputs=0
		
		while numOutputs != len(out):
			# Each round take as much as the pattern vector has keeping in mind we start taking from the first index...
			toTake=len(self.patternVector)-self.count
			# ... but if the pattern vector will give more than needed, only take the difference
			if len(out)-numOutputs < toTake:
				toTake=len(out)-numOutputs
			# take from the pattern vector starting at the current count
			out[numOutputs:numOutputs+toTake]=self.patternVector[self.count:self.count+toTake]
			# update the index to start taking from
			self.count=(self.count+toTake)%len(self.patternVector)
			numOutputs+=toTake
	
		return len(output_items[0])

