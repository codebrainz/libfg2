import fg2

fg = fg2.FrameGrabber("/dev/video0")

print repr(fg)
print str(fg)
print "inp:", fg.current_input
#fg.current_input = 1
print dir(fg)
