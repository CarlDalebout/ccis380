/*
  USAGE:

      glColorf(1, 0, 0);
      mygllib::Text::draw(0, 0, 2,          // x,y,z
                          "hello world",
                          0.0025,           // scale (default is 0.0025)
                          2.0);             // line width (default is 2.0)
));

 */

#ifndef TEXT_H
#define TEXT_H

namespace mygllib
{
    class Text
    {
    public:
        Text(const std::string & s="",
             float x=0, float y=0, float z=0,
             float scale=0.0025,
             float linewidth=2.0,
             void * font=GLUT_STROKE_ROMAN)
            : s_(s),
              x_(x), y_(y), z_(z),
              scale_(scale), linewidth_(linewidth), font_(font)
        {}
        
        void draw() const
        {
            glLineWidth(linewidth_);
            glPushMatrix();
            glTranslatef(x_, y_, z_);
            glScalef(scale_, scale_, scale_);
            for (unsigned int i = 0; i < s_.length(); i++)
            {
                glutStrokeCharacter(font_, s_[i]);
            }
            glPopMatrix();
            glLineWidth(1.0);
        }
        
        static void draw(const std::string & s,
                         float x, float y, float z,
                         float scale=0.0025,
                         float linewidth=2.0,
                         void * font=GLUT_STROKE_ROMAN)
        {
            Text(s, x, y, z, scale, linewidth, font).draw();
        }
        
    private:
        std::string s_;
        float x_, y_, z_;
        float scale_;
        float linewidth_;
        void * font_;
    };
}
#endif
