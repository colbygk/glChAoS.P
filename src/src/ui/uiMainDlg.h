//------------------------------------------------------------------------------
//  Copyright (c) 2018-2019 Michele Morrone
//  All rights reserved.
//
//  https://michelemorrone.eu - https://BrutPitt.com
//
//  twitter: https://twitter.com/BrutPitt - github: https://github.com/BrutPitt
//
//  mailto:brutpitt@gmail.com - mailto:me@michelemorrone.eu
//  
//  This software is distributed under the terms of the BSD 2-Clause license
//------------------------------------------------------------------------------
#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <IconsFontAwesome/IconsFontAwesome.h>
#ifdef GLCHAOSP_USE_MARKDOWN
#include <imgui_markdown/imgui_markdown.h>
#endif

void fillAttractorData();
void writePalette(const char *filename, int idx);
void setGUIStyle();

class particlesBaseClass;

#define DLG_BORDER_SIZE 2
#define INDENT(x) ((x)+border+2)

bool loadAttractorFile(bool fileImport = false, const char *file = nullptr);
void saveAttractorFile(bool fileExport = false);

class baseDlgClass
{
public:

    baseDlgClass(const char *title, bool visible=false) : wndTitle(title), isVisible(visible) {}
    //baseDlgClass(bool visible=false) : isVisible(visible) {}

    void visible(bool b) { isVisible = b; }
    bool visible() { return isVisible; }

    void toggleVisible() { isVisible^=true; }

    const char *getTitle() { return wndTitle.c_str(); }

    void rePosWndByMode(int x, int y);


protected:
    bool isVisible;
    std::string wndTitle;

};

class attractorDlgClass : public baseDlgClass
{
public:
    attractorDlgClass()  : baseDlgClass(" " ICON_FA_SUPERSCRIPT " - Attractors / Fractals", true) {}


/*
    void nMagnetsTestChange() {
        static int nMagnets=attractorsList.get()->getNumElements();
        if(attractorsList.get()->getNumElements() > nMagnets) {
            attractorsList.get()->vVal.resize(attractorsList.get()->getNumElements());   
            attractorsList.get()->kVal.resize(attractorsList.get()->getNumElements());
            nMagnets=attractorsList.get()->m_nMagnets;
        }
    }
*/
    void onGenerate() {}
    void onReload() {}
    void onRestart() {}

    void view();

private:
    int numElements;
};

class paletteDlgClass : public baseDlgClass
{
public:
    paletteDlgClass() : baseDlgClass(" " ICON_FA_TINT " Palette") { }

    void view();

protected:
};

                               

class particlesDlgClass : public baseDlgClass
{
public:

    particlesDlgClass() : baseDlgClass(" Particles", true) {}

    //pass string
    char *buildID(char *base, char idA, char idB) {
        base[2] = idA; 
        base[3] = idB;
        return base;
    }

    //void colorMapsSelectDlg(particlesBaseClass *particles, char id);
    //bool colCheckButton(bool b, const char *s, const float sz);
    void viewSettings(particlesBaseClass *particles, char id);

    void view();


    //int selectionMapOpen[2];

    void resetTreeParticlesFlags() { psTreeVisible = false; bbTreeVisible = false; }

private:
    bool psTreeVisible = false, bbTreeVisible = false;
    //particlesDataClass billboard, pointsprite;
};

class viewSettingDlgClass  : public baseDlgClass
{
public:
    viewSettingDlgClass() : baseDlgClass("View Tools") {}

    void view();

private:
};

#if !defined(GLCHAOSP_LIGHTVER)

class progSettingDlgClass  : public baseDlgClass
{
public:
    progSettingDlgClass() : baseDlgClass("Program settings") {}

    void view();

private:
};

class dataDlgClass  : public baseDlgClass
{
public:
    dataDlgClass() : baseDlgClass("Data") {}

    void view();

private:
};


#endif

class particleEditDlgClass  : public baseDlgClass
{
public:
    particleEditDlgClass() : baseDlgClass("Particle Edit") {}

    void view();

private:
};

class infoDlgClass  : public baseDlgClass
{
public:
    infoDlgClass() : baseDlgClass("Info") {}

    void view();


private:
    bool metricW = false;

};

class clippingDlgClass  : public baseDlgClass
{
public:
    clippingDlgClass() : baseDlgClass("Clipping planes") {}

    void view();

private:
};


class aboutDlgClass  : public baseDlgClass
{
public:
    aboutDlgClass() : baseDlgClass("About") {}

    void view();

private:
};

class fastViewDlgClass  : public baseDlgClass
{
public:
    fastViewDlgClass() : baseDlgClass("ChaoticAttractors/") {}

    void view();

private:
};

class imGuIZMODlgClass  : public baseDlgClass
{
public:
    imGuIZMODlgClass() : baseDlgClass("##giz", true) {}

    void view();


private:
};

class mainImGuiDlgClass  : public baseDlgClass
{
public:
    mainImGuiDlgClass() : baseDlgClass(" glChAoS.P", true)  {  }
    ~mainImGuiDlgClass() { }

    particlesDlgClass &getParticlesDlgClass() { return particlesDlg; } 


    void renderImGui();
    void postRenderImGui();
    void view();

    void switchMode(int x, int y);

/*
    void setTableAlterbateColor1(ImVec4 &c) { tableAlternateColor1 = c; }
    ImVec4 &getTableAlterbateColor1() { return tableAlternateColor1; }
    void setTableAlterbateColor2(ImVec4 &c) { tableAlternateColor2 = c; }
    ImVec4 &getTableAlterbateColor2() { return tableAlternateColor2; }
*/

    ImVec4 &getGuiThemeBaseColor() { return guiThemeBaseColor; }
    void setGuiThemeBaseColor(const ImVec4 &c) { guiThemeBaseColor =  c; }
    void setGuiThemeBaseColor(const ImVec4 *c) { guiThemeBaseColor = *c; }

    int getSelectedGuiTheme() { return selectedGuiTheme; };
    void setSelectedGuiTheme(int i) { selectedGuiTheme = i; };

    float getFontSize() { return fontSize; }
    float getFontZoom() { return fontZoom; }
    void setFontSize(float f) { fontSize = f; }
    void setFontZoom(float f) { fontZoom = f; }

    fastViewDlgClass & getfastViewDlg() { return fastViewDlg; }

#ifdef GLCHAOSP_USE_MARKDOWN
    ImGui::MarkdownConfig & getMarkDownConfig() { return mdConfig; }
#endif

#ifdef GLCHAOSP_LIGHTVER
    bool getInvertSettings() { return invertSettings; }
    void setInvertSettings(bool b) { invertSettings = b; }
#endif

private:
    ImVec4 guiThemeBaseColor = ImVec4(0.0f, 0.30f, 0.55f, 1.00f); //ImVec4(0.0f, 0.20f, 0.30f, 1.00f); //Solar; 
    int selectedGuiTheme = 0;

    bool fontChanged = false;
    float RasterizerMultiply = 1.0;
       
    float fontSize = 13.f, fontZoom = 1.f;

#ifdef GLCHAOSP_USE_MARKDOWN
    ImGui::MarkdownConfig mdConfig = { NULL, ICON_FA_LINK, { NULL, true, NULL, false, NULL, false } };
#endif



    ImFont *mainFont = nullptr, *iconFont = nullptr;
    //ImFont *testFont = nullptr;
    ImFontConfig fontCFG;

aboutDlgClass aboutDlg;
attractorDlgClass attractorDlg;
particlesDlgClass particlesDlg;
imGuIZMODlgClass imGuIZMODlg;
infoDlgClass infoDlg;
paletteDlgClass paletteDlg;
viewSettingDlgClass viewSettingDlg;
fastViewDlgClass fastViewDlg;
particleEditDlgClass particleEditDlg;
clippingDlgClass clippingDlg;
#if !defined(GLCHAOSP_LIGHTVER)
dataDlgClass dataDlg;
progSettingDlgClass progSettingDlg;
#else
    bool invertSettings = false;
#endif
private:

friend void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
friend void setGUIStyle();
friend class progSettingDlgClass;
friend class particlesDlgClass;
friend class viewSettingDlgClass;

};

