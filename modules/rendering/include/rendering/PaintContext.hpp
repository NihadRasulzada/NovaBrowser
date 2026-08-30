#pragma once

namespace NovaBrowser::Rendering {

class PaintContext {
public:
  PaintContext(void *native_context, int width, int height);

  void *NativeContext() const;

  int Width() const;

  int Height() const;

private:
  void *m_native_context;

  int m_width;
  int m_height;
};

} // namespace NovaBrowser::Rendering
