using Libfg2;

public static int main(int argc, string[] argv)
{
    FrameGrabber fg = new FrameGrabber("/dev/video0");
    Frame frame = fg.grab();
    frame.save("snapshot.jpg");
    return 0;
}
