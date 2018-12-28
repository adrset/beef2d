#ifndef BUTTON_H_
#define BUTTON_H_
#include <nanovg/nanovg.h>
#include <functional>
#include "Window.h"
#include "Renderable.h"
namespace ge{
  void defaultClick();

  class Button{
  public:
    Button(int x, int y, int w, int h, GLFWwindow* window, std::string text, NVGcolor a, NVGcolor b,int rounds = 0, float m_fontSize=20.0f, std::function<void()> click = defaultClick);
    void draw(NVGcontext* context);
    void setColors(NVGcolor a, NVGcolor b);
    bool isMouseOver(int x, int y);
    std::function<void()> click;
    void setText(std::string txt, float m_fontSize);
    bool isClicked();
  private:
  	
    GLFWwindow* m_window;
    int m_x, m_y, m_w, m_h;
    std::string m_text;
  	float m_fontSize;
    NVGcolor m_colorA;
    NVGcolor m_colorB;
    int  m_rounds;


  };



}
#endif
