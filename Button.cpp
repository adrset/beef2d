#include "Button.h"
namespace ge{
  Button::Button(int x, int y, int w, int h, GLFWwindow* window, std::string text, NVGcolor a, NVGcolor b,int rounds, float fontSize, std::function<void()> click /* has default param*/) :
  click(click), m_window(window), m_x(x), m_y(y), m_w(w), m_h(h), m_text(text), m_fontSize(fontSize),m_colorA(a), m_colorB(b),
  m_rounds(rounds){

  }

  void Button::setColors(NVGcolor a, NVGcolor b){
    this->m_colorA = a;
    this->m_colorB = b;
  }

  void defaultClick(){
    printf("Halo");
  }

  void Button::setText(std::string txt, float fontSize){
    this->m_text = txt;
    this->m_fontSize = fontSize;
  }

  bool Button::isMouseOver(int x, int y){
    if(x > m_x && x < m_x + m_w && y > m_y && y < m_y + m_h && ge::Window::currWindow == m_window){
      return true;
    }
    else{
      return false;
    }
  }

  bool Button::isClicked(){
    if(ge::InputManager::isMouseKeyPressed(GLFW_MOUSE_BUTTON_1) && isMouseOver(ge::InputManager::getMouseCoords().xy.x,
    ge::InputManager::getMouseCoords().xy.y)){
      click();
      return true;
    }else{
      return false;
    }
  }

  void Button::draw(NVGcontext* context){
    NVGpaint bg = nvgLinearGradient(context, 0,0,m_w,m_h, m_colorA, m_colorB);
    nvgBeginPath(context);
		nvgFillPaint(context, bg);
		nvgRoundedRect(context, m_x,m_y, m_w,m_h, m_rounds);
		nvgFill(context);
    nvgTextAlign(context,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);
    nvgFontSize(context, m_fontSize);
    nvgFontFace(context, "sans");
    nvgText(context, m_x+m_w/2.0,m_y+m_h/2.0, m_text.c_str(), NULL);
  }



}
