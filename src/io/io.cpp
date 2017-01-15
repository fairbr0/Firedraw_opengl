#include <iostream>
#include <string>
#include "pugixml.hpp"
#include <vector>
#include "io.h"
#include "Point.h"
#include "Color.h"
#include "Element.h"
#include <vector>
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"
#include "Context.h"

using namespace std;

/*io class.
    This class will save and load files in the XML format. It uses the
    pugixml parser, which is found here: http://pugixml.org/;
*/

io::io(Context *c)
{
    this->context = c;
}

void io::save(string s)
{
    /*This method goes through the shape, text and line list, and serialises
    each to XML. this is then stored in a file with a name of the passed string.
    */
    vector<Shape> *appShapes = this->context->getShapes();
    int objRef = this->context->getObjectId();
    pugi::xml_document doc;
    pugi::xml_node image = doc.append_child("image");
    image.append_child("objRef").text().set(context->getObjectId());

    pugi::xml_node shapes = image.append_child("shapes");

    for (int i = 0; i < appShapes->size(); i++) {
        Shape s = context->appShapes[i];
        Element elem = s.elem;
        pugi::xml_node shape = shapes.append_child("shape");
        string type = s.getType();
        shape.append_child("type").text().set(type.c_str());

        shape.append_child("objRef").text().set(s.getObjRef());
        pugi::xml_node lc =  shape.append_child("lineColor");
        lc.append_child("r").text().set(elem.getLineColor().getColors()[0]);
        lc.append_child("g").text().set(elem.getLineColor().getColors()[1]);
        lc.append_child("b").text().set(elem.getLineColor().getColors()[2]);
        lc.append_child("a").text().set(elem.getLineColor().getColors()[3]);

        pugi::xml_node fc =  shape.append_child("fillColor");
        fc.append_child("r").text().set(elem.getFillColor().getColors()[0]);
        fc.append_child("g").text().set(elem.getFillColor().getColors()[1]);
        fc.append_child("b").text().set(elem.getFillColor().getColors()[2]);
        fc.append_child("a").text().set(elem.getFillColor().getColors()[3]);
        shape.append_child("lineWeight").text().set(elem.getLineWeight());
        shape.append_child("filled").text().set(elem.getIsFilled());
        shape.append_child("width").text().set(s.getWidth());
        shape.append_child("height").text().set(s.getHeight());

        pugi::xml_node center = shape.append_child("center");
        center.append_child("x").text().set(s.getCenter().getPoint()[0]);
        center.append_child("y").text().set(s.getCenter().getPoint()[1]);
        shape.append_child("rotation").text().set(s.getRotation());
    }

    pugi::xml_node texts = image.append_child("texts");
    vector<Text> *appTexts = &this->context->appTexts;
    for (int i = 0; i < appTexts->size(); i++) {
      Text t = context->appTexts[i];
      Element elem = t.elem;

      pugi::xml_node text = texts.append_child("text");

      text.append_child("objRef").text().set(t.getObjRef());
      pugi::xml_node lc =  text.append_child("lineColor");
      lc.append_child("r").text().set(elem.getLineColor().getColors()[0]);
      lc.append_child("g").text().set(elem.getLineColor().getColors()[1]);
      lc.append_child("b").text().set(elem.getLineColor().getColors()[2]);
      lc.append_child("a").text().set(elem.getLineColor().getColors()[3]);

      pugi::xml_node fc =  text.append_child("fillColor");
      fc.append_child("r").text().set(elem.getFillColor().getColors()[0]);
      fc.append_child("g").text().set(elem.getFillColor().getColors()[1]);
      fc.append_child("b").text().set(elem.getFillColor().getColors()[2]);
      fc.append_child("a").text().set(elem.getFillColor().getColors()[3]);
      text.append_child("lineWeight").text().set(elem.getLineWeight());
      text.append_child("filled").text().set(elem.getIsFilled());
      text.append_child("width").text().set(t.getWidth());
      text.append_child("height").text().set(t.getHeight());

      pugi::xml_node center = text.append_child("center");
      center.append_child("x").text().set(t.getCenter().getPoint()[0]);
      center.append_child("y").text().set(t.getCenter().getPoint()[1]);
      text.append_child("rotation").text().set(t.getRotation());


      string label = t.getLabel();
      text.append_child("label").text().set(label.c_str());

    }

    pugi::xml_node lines = image.append_child("lines");
    vector<Line> *appLines = &this->context->appLines;
    for (int i = 0; i < appLines->size(); i++) {
        Line l = context->appLines[i];
        Element elem = l.elem;
        pugi::xml_node line = lines.append_child("line");

        line.append_child("objRef").text().set(l.getObjRef());
        pugi::xml_node lc =  line.append_child("lineColor");
        lc.append_child("r").text().set(elem.getLineColor().getColors()[0]);
        lc.append_child("g").text().set(elem.getLineColor().getColors()[1]);
        lc.append_child("b").text().set(elem.getLineColor().getColors()[2]);
        lc.append_child("a").text().set(elem.getLineColor().getColors()[3]);

        line.append_child("lineWeight").text().set(elem.getLineWeight());
        pugi::xml_node start = line.append_child("start");
        start.append_child("x").text().set(l.getP1().getPoint()[0]);
        start.append_child("y").text().set(l.getP1().getPoint()[1]);

        pugi::xml_node end = line.append_child("end");
        end.append_child("x").text().set(l.getP2().getPoint()[0]);
        end.append_child("y").text().set(l.getP2().getPoint()[1]);
    }

    string file = s;
    file += ".drw";
    doc.save_file(file.c_str());

}

void io::load(string s)
{
    /* This method will attempt to load a file with the passed name into the
    context. It will try and create shape, line and Text objects, then stored
    them into the context lists.
    */
    s += ".drw";
    const char* path = s.c_str();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path);
    //pugi::xml_parse_result result = doc.load_file("tree.xml");

    pugi::xml_node image = doc.child("image");
    pugi::xml_node shapes = image.child("shapes");
    pugi::xml_node texts = image.child("texts");
    pugi::xml_node lines = image.child("lines");

    this->context->resetAppShapes();
    this->context->resetTempShapes();

    int objRef = image.child("objRef").text().as_int();
    this->context->setObjectId(objRef);
    std::vector<Shape> shapeObjects;

    for (pugi::xml_node_iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        Point p(it->child("center").child("x").text().as_float(), it->child("center").child("y").text().as_float());
        float w = it->child("width").text().as_float();
        float h = it->child("height").text().as_float();
        int objRef = it->child("objRef").text().as_int();

        pugi::xml_node color = it->child("fillColor");
        float r = color.child("r").text().as_float();
        float g = color.child("g").text().as_float();
        float b = color.child("b").text().as_float();
        float a = color.child("a").text().as_float();
        Color fc(r, g, b, a);

        color = it->child("lineColor");
        r = color.child("r").text().as_float();
        g = color.child("g").text().as_float();
        b = color.child("b").text().as_float();
        a = color.child("a").text().as_float();
        Color lc(r, g, b, a);

        bool filled = it->child("filled").text().as_bool();

        float lw = it->child("lineWeight").text().as_float();
        Element elem(filled, lw, lc, fc);

        Shape temp;
        string type = it->child("type").text().get();
        if (type == "SQUARE") {
             temp = Square(p, w, h, objRef, elem, "SQUARE");
        } else if (type == "CIRCLE") {
            temp = Circle(p, w, h, objRef, elem, "CIRCLE");
        } else if (type == "TRIANGLE") {
            temp = Triangle(p, w, h, objRef, elem, "TRIANGLE");
        }

        temp.setRotation(it->child("rotation").text().as_float());

        shapeObjects.push_back(temp);

    }
    this->context->setShapes(shapeObjects);

    std::vector<Text> textObjects;
    for (pugi::xml_node_iterator it = texts.begin(); it != texts.end(); ++it)
    {
        Point p(it->child("center").child("x").text().as_float(), it->child("center").child("y").text().as_float());
        float w = it->child("width").text().as_float();
        float h = it->child("height").text().as_float();
        int objRef = it->child("objRef").text().as_int();

        pugi::xml_node color = it->child("fillColor");
        float r = color.child("r").text().as_float();
        float g = color.child("g").text().as_float();
        float b = color.child("b").text().as_float();
        float a = color.child("a").text().as_float();
        Color fc(r, g, b, a);

        color = it->child("lineColor");
        r = color.child("r").text().as_float();
        g = color.child("g").text().as_float();
        b = color.child("b").text().as_float();
        a = color.child("a").text().as_float();
        Color lc(r, g, b, a);

        bool filled = it->child("filled").text().as_bool();

        float lw = it->child("lineWeight").text().as_float();
        Element elem(filled, lw, lc, fc);

        Text temp;
        string label = it->child("label").text().get();
        temp = Text(label, p, w, h, objRef, elem, "TEXT");

        temp.setRotation(it->child("rotation").text().as_float());

        textObjects.push_back(temp);
    }

    this->context->appTexts = textObjects;

    std::vector<Line> lineObjects;
    for (pugi::xml_node_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        Point p(it->child("start").child("x").text().as_float(), it->child("start").child("y").text().as_float());
        Point q(it->child("end").child("x").text().as_float(), it->child("end").child("y").text().as_float());
        int objRef = it->child("objRef").text().as_int();

        pugi::xml_node color = it->child("lineColor");
        float r = color.child("r").text().as_float();
        float g = color.child("g").text().as_float();
        float b = color.child("b").text().as_float();
        float a = color.child("a").text().as_float();
        Color lc(r, g, b, a);

        float lw = it->child("lineWeight").text().as_float();
        Element elem(false, lw, lc, lc);

        Line line(p, q, objRef, elem, "LINE");
        lineObjects.push_back(line);
    }

    this->context->appLines = lineObjects;
}
