CXXFLAGS = -O2 -g -Wall -Wno-unused-result -std=gnu++11 -fmessage-length=0
OBJS = osmToString.o
LIBS =
TARGET = osmToString
$(TARGET):$(OBJS)
$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
all:$(TARGET)
clean:
rm -f $(OBJS) $(TARGET)
