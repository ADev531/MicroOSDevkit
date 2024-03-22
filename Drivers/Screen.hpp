class Mode {
public:
   int width;
   int height;

   Mode(int w, int h) {
      width = w;
      height = h;
   }
};

class Screen {
   public:
      int Width;
      int Height;

      virtual void DrawPixel(int x, int y, char c) {}
      virtual void DrawFilledRect(int x, int y, int width, int height, char c) {}
      virtual void SetMode(int width, int height) {}
};