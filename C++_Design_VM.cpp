#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

class Shape {
    string color;
public:
    Shape() = default;
    Shape(string col) : color(col){}
    virtual ~Shape() = default;
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual void display() noexcept {
        cout << "area = " << area()<<endl;
        cout << "perimeter = " << perimeter() << endl;
    }
        
};

class Circle : public Shape {
    double rad;
public: 
    Circle() = default;
    Circle(string col, double d) : rad(d), Shape(col) { }
    virtual double area() override { return 3.14 * rad * rad; }
    virtual double perimeter() override { return 31.4 * rad; }

};

class Rectangle : public Shape {
    double width;
    double height;
public:
    Rectangle() = default;
    Rectangle(string col, double w, double h) : width(w), height(h), Shape(col) { }
    virtual double area() override { return (width * height); }
    virtual double perimeter() override { return (width + height) ; }

};

class ShapeProcessor {
    vector<Shape*> allShape;
public: 
    ShapeProcessor() = default;
    void addShape(Shape* shape) noexcept{
        allShape.push_back(shape);
    }

    void processCommands(vector<string> cmd);
    void executeCommand(string cmd);
    double areaOfCircle() noexcept;
    void displayAll() const;
    double perimeterOfRectangle() noexcept;
};


void ShapeProcessor::processCommands(vector<string> cmd) {
    vector<thread> vectThread;
    for (auto &c : cmd) {
        vectThread.emplace_back(thread(&ShapeProcessor::executeCommand, this, c));
    }
    this_thread::sleep_for(chrono::milliseconds(100));

    size_t len = vectThread.size();
    for (int i = 0 ; i != len; ++i)
        vectThread[i].join();
}

void ShapeProcessor::executeCommand(string cmd) {
    if (cmd.compare("areaOfCircle") == 0)
        areaOfCircle();
    else if (cmd.compare("displayAll") == 0)
        displayAll();
    else if (cmd.compare("perimeterOfRectangle") == 0)
        perimeterOfRectangle();   
}

double ShapeProcessor::areaOfCircle() noexcept{
    for (auto & s : allShape) {
        if (Circle* cir = dynamic_cast<Circle*>(s))
            return cir->area();
        else if (Rectangle* rect = dynamic_cast<Rectangle*>(s))
            return rect->area();
   }

    return 0;
}

void ShapeProcessor::displayAll() const {
    for (auto &s : allShape) {
        if (Circle* cir = dynamic_cast<Circle*>(s))
            cir->display();
        else if (Rectangle* rect = dynamic_cast<Rectangle*>(s))
            rect->display();
    }
}

double ShapeProcessor::perimeterOfRectangle() noexcept {
    for (auto &s : allShape) {
        if (Circle* cir = dynamic_cast<Circle*>(s))
            return cir->perimeter();
        else if (Rectangle* rect = dynamic_cast<Rectangle*>(s))
            return rect->perimeter();
    }

    return 0;
}

int main() {
    ShapeProcessor processor;
    processor.addShape(new Circle("Red", 5.0));
    processor.addShape(new Rectangle("Blue", 4.0, 6.0));
    processor.addShape(new Circle("Yellow", 3.0));

    std::vector<std::string> commands = { "displayAll", "areaOfCircle", "perimeterOfRectangle" }; //area of circle (3.14 * radius * radius) // perimeterofRectangle (2 * (lenght * width))
    processor.processCommands(commands);

    return 0;
}
/*
// Function to find parity of number `n`
bool findParity(unsigned n)
{
    bool parity = false;

    // run till `n` becomes 0
    while (n)
    {
        // invert the parity flag
        if (n & 1) {
            parity = !parity;
        }

        // right shift `n` by 1 (divide by 2)
        n = n >> 1;
    }

    return parity;
}

int main()
{
    unsigned n = 31;

    cout << n << " in binary is " << bitset<8>(n) << endl;

    if (findParity(n)) {
        cout << "The parity of " << n << " is odd";
    }
    else {
        cout << "The parity of " << n << " is even";
    }

    return 0;
}
*/