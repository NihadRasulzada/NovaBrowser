#pragma once
#include "ui/Node.hpp"
#include <memory>

namespace Nova::UI {

class View {
public:
  View(std::shared_ptr<Node> node) : m_node(std::move(node)) {}

  Node *operator->() const { return m_node.get(); }
  Node &operator*() const { return *m_node; }
  const std::shared_ptr<Node> &GetNode() const { return m_node; }

private:
  std::shared_ptr<Node> m_node;
};

} // namespace Nova::UI
