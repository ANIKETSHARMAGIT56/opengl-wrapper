#pragma once

namespace GLwrap {

class IndexBuffer {
private:
  unsigned int m_RendererID;
  unsigned int m_Count;

public:
  IndexBuffer(const unsigned int *data, unsigned int count);
  ~IndexBuffer();

  void Bind();
  void UnBind();
  void Update(const void *data, unsigned int size) const;
  inline unsigned int GetCount() const { return m_Count; }
};
} // namespace GLwrap