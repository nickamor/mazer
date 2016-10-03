//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include <vector>
#include <sstream>
#include "maze_svg_writer.h"

using namespace mazer;

MazeSvgWriter::MazeSvgWriter(const std::string &filename) : filename(filename)
{

}

struct SvgElem
{
    virtual ~SvgElem() = 0;
    virtual std::string ToString() const = 0;
};

struct Document : public SvgElem
{
    static constexpr double width = 210;
    static constexpr double height = 297;

    const double x, y, w, h;

    std::vector<SvgElem*> children;

    Document(double x, double y, double w, double h) :
        x(x), y(y), w(w), h(h) {}
    ~Document() {
        while (children.size() > 0) {
            SvgElem* elem = children.front();
            delete elem;
            children.erase(children.begin());
        }
    }

    std::string ToString() const;

    void AddChild(SvgElem* elem);
};

struct Rect : public SvgElem {
    const double width, height;

    Rect(double width, double height) :
        width(width), height(height) {}
    ~Rect() {}

    std::string ToString() const;
};

struct Line : public SvgElem {
    const double x1, y1, x2, y2;

    Line(double x1, double y1, double x2, double y2) : 
        x1(x1), y1(y1), x2(x2), y2(y2) {}
    ~Line() {}

    std::string ToString() const;
};

SvgElem::~SvgElem() {}

std::ostream& operator<<(std::ostream& os, const SvgElem& elem) {
    os << elem.ToString();
    return os;
}

std::string
Document::ToString() const {
    std::stringstream ss;
    ss << "<svg viewBox='0 0 " << w << " " << h;
    ss << "' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>\n";
    
    for (auto& child : children) {
        ss << *child << '\n';
    }

    ss << "</svg>";
    return ss.str();

}

void
Document::AddChild(SvgElem *elem) {
    children.push_back(elem);
}

std::string
Rect::ToString() const {
    std::stringstream ss;
    ss << "<rect width='" << width;
    ss << "' height='" << height;
    ss << "' style='fill: black' />";
    return ss.str();
}

std::string
Line::ToString() const {
    std::stringstream ss;
    ss << "<line stroke='white' stroke-width='1' ";
    ss << "x1='" << x1 << "' ";
    ss << "y1='" << y1 << "' ";
    ss << "x2='" << x2 << "' ";
    ss << "y2='" << y2 << "'/>";
    return ss.str();
}

void
MazeSvgWriter::Write(std::shared_ptr<Maze> maze)
{
    std::ofstream out(filename);

    int w = maze->GetWidth(), h = maze->GetHeight();
    const int cell_w = 10, cell_h = 10;
    const int x_origin = cell_w / 2, y_origin = cell_h / 2;

    Document doc(0, 0, (w + 1) * cell_w, (h + 1) * cell_h);

    doc.AddChild(new Rect((w + 1) * cell_w, (h + 1) * cell_h));

    for (auto &edge : maze->GetEdges())
    {
        doc.AddChild(new Line(x_origin + (edge.src.x * cell_w), 
                                y_origin + (edge.src.y * cell_h),
                                x_origin + (edge.dst.x * cell_w),
                                y_origin + (edge.dst.y * cell_h)));
    }

    out << doc << '\n';

    out.close();
}
