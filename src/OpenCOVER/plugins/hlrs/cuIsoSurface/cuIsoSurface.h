/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef CUISOSURFACE_H
#define CUISOSURFACE_H

#include <map>

#include <sysdep/opengl.h>
#include <osg/Drawable>
#include <osg/Version>

#include <util/coTypes.h>
#include <cover/coVRPlugin.h>
#include <cover/ui/Owner.h>

#include <cover/coVRTui.h>

struct State;
class IsoDrawable;

namespace opencover
{
class coVRPlugin;

namespace ui
{
class Menu;
class Button;
class Slider;
}
}

using namespace opencover;

struct minmax
{
    float min, max;
};

/*
 * Author: Florian Niebling
 */
class cuIsoSurface : public coVRPlugin, public ui::Owner
{
public:
    cuIsoSurface();
    ~cuIsoSurface();
    void removeObject(const char *name, bool replace);
    void addObject(const RenderObject *container, osg::Group *, const RenderObject *, const RenderObject *, const RenderObject *, const RenderObject *);

    virtual bool init();
    virtual void preDraw(osg::RenderInfo &);
    virtual void preFrame();
    virtual void postFrame();
    /*
   static void getMinMax(const float *data, int numElem, float &min,
                         float &max, float minV = -FLT_MAX, float maxV = FLT_MAX);
   static void removeSpikesAdaptive(const float *data, int numElem,
                                    float &min, float &max);
   static void countBins(const float *data, int numElem, float min, 
                         float max, int numBins, int *bins);
   */
private:
    bool initDone;
    ui::Menu *menu = nullptr;
    coTUITab *tuiTab;
    std::map<std::string, osg::Geode *> geode;
    std::map<std::string, ui::Slider *> sliders;
    std::map<std::string, coTUIFloatSlider *> tuiSliders;
    std::map<std::string, coTUIToggleButton *> tuiButtons;
    std::map<std::string, osg::Group *> groups;

    std::map<std::string, struct minmax> minMax;
};

class IsoDrawable : public osg::Drawable, public coTUIListener
{
public:
    //   IsoDrawable(coSliderMenuItem *slider, coTUIFloatSlider *tui,
    IsoDrawable(ui::Slider *slider, coTUIFloatSlider *tui,
                coTUIToggleButton *button,
                const RenderObject *geo, const RenderObject *map, const RenderObject *data,
                float *bbox, float min, float max);
    IsoDrawable(const IsoDrawable &draw, const osg::CopyOp &op = osg::CopyOp::SHALLOW_COPY);
    ~IsoDrawable();

    virtual void drawImplementation(osg::RenderInfo &info) const;
    virtual osg::Object *cloneType() const;
    virtual osg::Object *clone(const osg::CopyOp &op) const;
#if OSG_VERSION_GREATER_OR_EQUAL(3, 3, 2)
    virtual osg::BoundingBox computeBoundingBox() const;
#else
    virtual osg::BoundingBox computeBound() const;
#endif

    void preFrame();
    void preDraw();
    void postFrame();

    virtual void tabletEvent(coTUIElement *tUIItem);

private:
    State *state;

    const RenderObject *geom;
    float *data;

    bool changed;
    bool animate;
    int anim;
    float threshold;
    float min, max;

    ui::Slider *slider = nullptr;
    coTUIFloatSlider *tuiSlider;
    coTUIToggleButton *tuiButton;

    osg::BoundingBox box;
};

#endif
