#include "JsonSerializer.h"

namespace sintetizador_monofonico {

juce::Result JsonSerializer::saveToStream(
    const juce::ValueTree& state,
    juce::OutputStream& output)
{
  if (!state.isValid())
    return juce::Result::fail("Invalid ValueTree");

  auto json =
      valueTreeToVar(state);

  juce::JSON::writeToStream(
      output,
      json,
      juce::JSON::FormatOptions{}
          .withSpacing(
              juce::JSON::Spacing::multiLine)
          .withMaxDecimalPlaces(4));

  return juce::Result::ok();
}

juce::Result JsonSerializer::loadFromStream(
    juce::ValueTree& state,
    juce::InputStream& input)
{
  auto jsonText =
      input.readEntireStreamAsString();

  juce::var parsed;

  auto result =
      juce::JSON::parse(jsonText, parsed);

  if (result.failed())
    return result;

  state = varToValueTree(parsed);

  if (!state.isValid())
    return juce::Result::fail(
        "Failed to rebuild ValueTree");

  return juce::Result::ok();
}

juce::var JsonSerializer::valueTreeToVar(
    const juce::ValueTree& tree)
{
  auto* object = new juce::DynamicObject();

  // =========================================
  // TYPE
  // =========================================
  object->setProperty(
      "type",
      tree.getType().toString());

  // =========================================
  // PROPERTIES
  // =========================================
  auto* properties = new juce::DynamicObject();

  for (int i = 0; i < tree.getNumProperties(); ++i)
  {
    const auto name =
        tree.getPropertyName(i);

    properties->setProperty(
        name.toString(),
        tree[name]);
  }

  object->setProperty(
      "properties",
      juce::var(properties));

  // =========================================
  // CHILDREN
  // =========================================
  juce::Array<juce::var> children;

  for (int i = 0; i < tree.getNumChildren(); ++i)
  {
    children.add(
        valueTreeToVar(
            tree.getChild(i)));
  }

  object->setProperty(
      "children",
      children);

  return juce::var(object);
}

juce::ValueTree JsonSerializer::varToValueTree(
    const juce::var& v)
{
  auto* obj = v.getDynamicObject();

  if (obj == nullptr)
    return {};

  juce::ValueTree tree(
      obj->getProperty("type").toString());

  // =========================================
  // PROPERTIES
  // =========================================
  auto props =
      obj->getProperty("properties");

  if (auto* propObj = props.getDynamicObject())
  {
    for (const auto& property : propObj->getProperties())
    {
      tree.setProperty(
          property.name,
          property.value,
          nullptr);
    }
  }

  // =========================================
  // CHILDREN
  // =========================================
  auto children =
      obj->getProperty("children");

  if (children.isArray())
  {
    for (const auto& child : *children.getArray())
    {
      tree.addChild(
          varToValueTree(child),
          -1,
          nullptr);
    }
  }

  return tree;
}

}