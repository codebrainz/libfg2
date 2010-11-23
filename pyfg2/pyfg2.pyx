
cimport pyfg2
cimport cpython

cdef class FrameGrabber:

	cdef char *dev_name
	cdef pyfg2.fg_grabber *_fg
	
	def __cinit__(self, char *dev_name):
		
		self.dev_name = dev_name
		self._fg = pyfg2.fg_open(self.dev_name)
		
		if self._fg is NULL:
			cpython.PyErr_NoMemory()

	def __dealloc__(self):
		if self._fg is not NULL:
			pyfg2.fg_close(self._fg)
