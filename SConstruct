# SConstruct for libfg2

import os, sys
from collections import namedtuple


PREFIX   = "/usr/local"

SOURCE_DIR   = "src"
LIBRARY_DIR  = "lib"
HEADER_DIR   = "include"
BINARY_DIR   = "bin"
BUILD_SHARED = True
BUILD_STATIC = True
LIBRARY_SOURCE_FILES    = ["capture.c", "frame.c", "control.c"]
PROGRAM_SOURCE_FILES    = ["example.c", "test.c", "fg-udev.c"]

LIBNAME     = lambda n,e: os.path.join(LIBRARY_DIR, "lib%s.%s" % (n, e))
SH_LIBNAME  = lambda n: os.path.join(LIBRARY_DIR, "lib%s.so" % n)
ST_LIBNAME  = lambda n: os.path.join(LIBRARY_DIR, "lib%s.a" % n)
BINNAME     = lambda n: os.path.join(BINARY_DIR, "%s" % n)
DEPEND      = namedtuple("Dep", "name header required define arg")

LIBFG_DEPENDS = {

    "libv4l2":        DEPEND(
                        name="libv4l2",     # Lib name as in -lname
                        header="libv4l2.h", # Header file for lib
                        required=True,      # Mandatory dependency
                        define=None,        # A cc flag to define
                        arg=False),         # Name of option
                        
    "imlib2":         DEPEND("Imlib2", "Imlib2.h", False, "-DWITH_IMLIB2", "with_imlib2"),
    "gdk-pixbuf-2.0": DEPEND("gdk-pixbuf-2.0", "gdk-pixbuf/gdk-pixbuf.h", False, "-DWITH_GDKPIXBUF", "with_gdk_pixbuf"),
    "sdl":            DEPEND("SDL", "SDL.h", False, "-DWITH_SDL", "with_sdl"),
    "opencv":         DEPEND("cv", "cv.h", False, "-DWITH_OPENCV", "with_opencv")
}

AddOption("--prefix", dest="prefix", default=PREFIX, help="Installation prefix.")
AddOption("--debugging", dest="debug", default=False, action="store_true",
    help="Enable debugging information.")
AddOption("--no-static", dest="no_static", default=False, action="store_true",
    help="Don't build static library.")
AddOption("--no-shared", dest="no_shared", default=False, action="store_true",
    help="Don't build shared library.")
AddOption("--without-jpeglib", dest="without_jpeglib", action="store_true", default=False,
    help="Don't support writing JPEG files.")
AddOption("--with-imlib2", dest="with_imlib2", action="store_true", default=False,
    help="Support Imlib2 Images.")
AddOption("--with-gdk-pixbuf", dest="with_gdk_pixbuf", action="store_true", default=False,
    help="Support GDK Pixbufs.")
AddOption("--with-sdl", dest="with_sdl", action="store_true", default=False,
    help="Support SDL Surfaces.")
AddOption("--with-opencv", dest="with_opencv", action="store_true", default=False,
    help="Support OpenCV Images.")
AddOption("--with-docs", dest="with_docs", action="store_true", default=False,
    help="Use Doxygen to generate documentation.")

lib_env = Environment()
conf = Configure(lib_env)

if GetOption("debug"):
    lib_env.Append(CCFLAGS=["-g", "-Wall", "-Werror", "-DDEBUG"])

for lib, dep in LIBFG_DEPENDS.items():
    if dep.required or GetOption(dep.arg):
        lib_env.ParseConfig("pkg-config %s --cflags --libs" % lib)
        if not conf.CheckLibWithHeader(dep.name, dep.header, "c"):
            if dep.required:
                sys.stderr.write("E: Required package %s is missing, cannot proceed.\n" % prop[0])
                Exit(1)
            else:
                sys.stdout.write("W: Requested library %s is missing, not using feature.\n")
        else:
            if dep.define is not None:
                lib_env.Append(CCFLAGS=dep.define)

if not GetOption("without_jpeglib"):
    lib_env.Append(CCFLAGS="-DWITH_JPEGLIB", LIBS=["jpeg"])
# should have checked for existence of jpeglib

if any( GetOption(o) for o in ["with_imlib2","with_gdk_pixbuf","with_sdl"] ):
    LIBRARY_SOURCE_FILES.append("convert.c")

if not GetOption("no_static"):
    lib_static = lib_env.StaticLibrary(ST_LIBNAME("fg2"), LIBRARY_SOURCE_FILES, srcdir=SOURCE_DIR)

if not GetOption("no_shared"):
    lib_shared = lib_env.SharedLibrary(SH_LIBNAME("fg2"), LIBRARY_SOURCE_FILES, srcdir=SOURCE_DIR)
    
lib_env.Append(CPPPATH=HEADER_DIR, LIBPATH=LIBRARY_DIR)

lib_env = conf.Finish()

# build each program (only works with 1 .c file per program)
pgm_env = Environment()
pgm_env.Append(LIBS="fg2", CPPPATH=HEADER_DIR, LIBPATH=LIBRARY_DIR)
for pgm in PROGRAM_SOURCE_FILES:
    pgm_env.Program(BINNAME(pgm.replace(".c","")), pgm, srcdir=SOURCE_DIR)

pgm_env.Program(BINNAME("camview"), "camview.c", srcdir=SOURCE_DIR, LIBS=["SDL", "fg2"])

if GetOption("with_docs"):
    import subprocess
    if not os.path.exists(os.path.join("share", "doc")):
        os.makedirs(os.path.join("share","doc"))
    subprocess.call(["doxygen", "Doxyfile"])
# todo: add cleanup code

#import distutils.sysconfig
#py_env = Environment(SWIGFLAGS=['-python'],
            #CPPPATH=[distutils.sysconfig.get_python_inc()],
            #SHLIBPREFIX="")
#py_env.Append(CPPPATH=HEADER_DIR, LIBPATH=LIBRARY_DIR)


#py_env.SharedLibrary(SH_LIBNAME("pyfg2"), [
                #py_env.SharedObject(target="capture.op", source="capture.c", srcdir=SOURCE_DIR),
                #py_env.SharedObject(target="frame.op", source="frame.c", srcdir=SOURCE_DIR),
                #py_env.SharedObject(target="convert.op", source="convert.c", srcdir=SOURCE_DIR),
                #"libfg2.interface"])












