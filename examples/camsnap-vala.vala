using Libfg2;

static int main(string[] args)
{
    FrameGrabber fg = new FrameGrabber("/dev/video0");
    Frame frame = fg.grab();
    frame.save("snapshot.jpg");
    return 0;
}
