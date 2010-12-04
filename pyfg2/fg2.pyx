cimport fg2
cimport cpython

import errno


cdef class FrameGrabber:

    cdef fg2.fg_grabber *_fg

    def __cinit__(self, char *device_name):

        self._fg = fg2.fg_open(device_name)
        
        if self._fg is NULL:
            raise IOError(errno.EINVAL, 
                "Unable to open FrameGrabber '%s'" % device_name)
        
    def __dealloc__(self):
        
        if self._fg is not NULL:
            fg2.fg_close(self._fg)
    
    def __repr__(self):
        return "FrameGrabber(%r)" % self.device_name
    
    def __str__(self):
        return self.device_name
            
    property device_name:
        def __get__(self):
            return self._fg.device
    
    property fileno:
        def __get__(self):
            return self._fg.fd
    
    property current_input:
        
        def __get__(self):
            return fg_get_input(self._fg)
        
        def __set__(self, index):
            if fg_set_input(self._fg, index) != 0:
                raise Exception("Cannot set input to %d" % index)
    
    
#cdef class Input:

    #cdef readonly int index
    
    #def __cinit__(self, FrameGrabber fg, int index):
        
        #self._fg = fg
        
        #if index < 0 or index >= self._fg._fg.num_inputs:
            #raise IndexError()
        
        #self.index = index

    #def __repr__(self):
        #return "Input(device=%r, index=%r)" % (self._fg.device_name, self.index)
    
    #def __str__(self):
        #return "%s:%d (%s)" % (self._fg.device_name, self.index, self.name)

    #property name:
        #def __get__(self):
            
            #return self._fg._fg.inputs[self.index]


