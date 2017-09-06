
#include "GcodeUpdater.h"
#include <string>
#include <sstream>

GcodeUpdater::GcodeUpdater(std::istream& input, std::ostream& output)
  : m_input(input)
  , m_output(output)
  , m_hasNextPoint(false)
  , m_originalNextPoint{0, 0, 0, 0}
  , m_nextPoint{0, 0, 0, 0}
  , m_nextCommand("")
  , m_firstPointFound(false)
{
}

bool GcodeUpdater::hasNextPoint()
{
  if (m_firstPointFound) {
    printPoint();
  }

  findNextPoint();

  return m_hasNextPoint;
}

const GcodeUpdater::Point& GcodeUpdater::nextPoint() const
{
  return m_originalNextPoint;
}

void GcodeUpdater::updatePoint(const Point& p)
{
  m_nextPoint = p;
}

void GcodeUpdater::updatePoint(Point&& p)
{
  m_nextPoint = std::move(p);
}

void GcodeUpdater::findNextPoint()
{
  m_firstPointFound = true;
  m_hasNextPoint = false;

  while(!m_input.eof() && !m_hasNextPoint && m_input.good()) {
    std::string buf;
    std::getline(m_input, buf);

    if (extractPoint(buf)) {
      m_hasNextPoint = true;
    } else {
      m_output << buf << std::endl;
    }
  }
}

bool GcodeUpdater::extractPoint(const std::string& str)
{
  auto stream = std::istringstream(str);
  std::string tmpCommand;

  stream >> tmpCommand;

  if (tmpCommand != "G00" && tmpCommand != "G01") {
    return false;
  }

  m_nextCommand = tmpCommand;

  auto& originalNextPoint = m_originalNextPoint;
  auto readAndStore = [&stream, &originalNextPoint](int index) {
    double v;
    stream >> v;
    originalNextPoint[index] = v;
  };

  while(stream) {
    char c;
    double v;

    stream.get(c);

    switch (c) {
    case 'X':
      readAndStore(0);
      break;
    case 'Y':
      readAndStore(1);
      break;
    case 'Z':
      readAndStore(2);
      break;
    case 'E':
      readAndStore(3);
      break;
    default:
      break;
    }
  }

  m_nextPoint = m_originalNextPoint;

  return true;
}

void GcodeUpdater::printPoint()
{
  m_output << m_nextCommand << " X" << m_nextPoint[0] << " Y" << m_nextPoint[1] << " Z" << m_nextPoint[2] << " E" << m_nextPoint[3] << std::endl;
}
