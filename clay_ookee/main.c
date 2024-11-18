#define CLAY_EXTEND_CONFIG_RECTANGLE Clay_String link; bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#include "clay/clay.h"
#define BGLIB_IMPLEMENTATION
#include "bg_lib.h"

double windowWidth = 1024, windowHeight = 768;
float PAGE_PADDING = 0.0f;
float modelPageOneZRotation = 0;
uint32_t ACTIVE_RENDERER_INDEX = 0;

const uint32_t FONT_ID_BODY_16 = 0;
const uint32_t FONT_ID_TITLE_56 = 1;
const uint32_t FONT_ID_BODY_24 = 2;
const uint32_t FONT_ID_BODY_36 = 3;
const uint32_t FONT_ID_TITLE_36 = 4;
const uint32_t FONT_ID_MONOSPACE_24 = 5;

const Clay_Color COLOR_LIGHT = (Clay_Color) {255, 255, 255, 255};
const Clay_Color COLOR_LIGHT_HOVER = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_RED = (Clay_Color) {168, 66, 28, 255};
const Clay_Color COLOR_RED_HOVER = (Clay_Color) {148, 46, 8, 255};
const Clay_Color COLOR_ORANGE = (Clay_Color) {225, 138, 50, 255};
const Clay_Color COLOR_BLUE = (Clay_Color) {111, 173, 162, 255};
const Clay_Color COLOR_BLACK = (Clay_Color) {0,0,0, 255};
const Clay_Color COLOR_WHITE = (Clay_Color) {255,255,255, 255};
const Clay_Color COLOR_GREY = (Clay_Color) {102,102,102, 255};


#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) (Clay_Vector2) { .x = (vector).x, .y = (vector).y }

Clay_TextElementConfig headerTextConfig = (Clay_TextElementConfig) { .fontId = 2, .fontSize = 24, .textColor = {61, 26, 5, 255} };
Clay_TextElementConfig blobTextConfig = (Clay_TextElementConfig) { .fontId = 2, .fontSize = 30, .textColor = {244, 235, 230, 255} };

void LandingPageDesktop() {
    CLAY(CLAY_ID("LandingPage1Desktop"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT({ .min = windowHeight * 0.25f }) }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = { .x = PAGE_PADDING } })) {
        CLAY(CLAY_ID("LandingPage1"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = { 32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2 }, .right = { 2 } })) {
            CLAY(CLAY_ID("LeftText"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(0.55f) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("Designer graphique, DA & DC"), CLAY_TEXT_CONFIG({ .fontSize = 16, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_BLACK }));
                CLAY_TEXT(CLAY_STRING("C’est bien moi — "), CLAY_TEXT_CONFIG({ .fontSize = 36, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_BLACK }));
                CLAY_TEXT(CLAY_STRING("Christiane"), CLAY_TEXT_CONFIG({ .fontSize = 36, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_BLACK }));
                CLAY_TEXT(CLAY_STRING("Bienvenue dans mon studio"), CLAY_TEXT_CONFIG({ .fontSize = 16, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_BLACK }));
            }
            CLAY(CLAY_ID("HeroImageOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_PERCENT(0.45f) }, .childAlignment = { CLAY_ALIGN_X_RIGHT } })) {
                CLAY(CLAY_ID("HeroSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
                CLAY(CLAY_ID("RotateLogo"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIT({ .min = 100 }) } }),CLAY_IMAGE({ .sourceDimensions = { 636, 636 }, .sourceURL = CLAY_STRING("/clay/images/ookee_Favicon.png") }));
            }
        }
    }
}

// void LandingPageMobile() {
//     CLAY(CLAY_ID("LandingPage1Mobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT({ .min = windowHeight - 70 }) }, .childAlignment = {CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}, .padding = { 16, 32 }, .childGap = 32 })) {
//         CLAY(CLAY_ID("LeftText"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
//             CLAY_TEXT(CLAY_STRING("Clay is a flex-box style UI auto layout library in C, with declarative syntax and microsecond performance."), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
//             CLAY(CLAY_ID("LandingPageSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(32) } })) {}
//             CLAY_TEXT(CLAY_STRING("Clay is laying out this webpage right now!"), CLAY_TEXT_CONFIG({ .fontSize = 32, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_ORANGE }));
//         }
//         CLAY(CLAY_ID("HeroImageOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_GROW() }, .childAlignment = { CLAY_ALIGN_X_CENTER }, .childGap = 16 })) {
//             // LandingPageBlob(1, 28, COLOR_BLOB_BORDER_5, CLAY_STRING("High performance"), CLAY_STRING("/clay/images/check_5.png"));
//             // LandingPageBlob(2, 28, COLOR_BLOB_BORDER_4, CLAY_STRING("Flexbox-style responsive layout"), CLAY_STRING("/clay/images/check_4.png"));
//             // LandingPageBlob(3, 28, COLOR_BLOB_BORDER_3, CLAY_STRING("Declarative syntax"), CLAY_STRING("/clay/images/check_3.png"));
//             // LandingPageBlob(4, 28, COLOR_BLOB_BORDER_2, CLAY_STRING("Single .h file for C/C++"), CLAY_STRING("/clay/images/check_2.png"));
//             // LandingPageBlob(5, 28, COLOR_BLOB_BORDER_1, CLAY_STRING("Compile to 15kb .wasm"), CLAY_STRING("/clay/images/check_1.png"));
//         }
//     }
// }

void FeatureBlocksDesktop(Clay_ScrollContainerData scrollData,float lerpValue) {
    float value = -(scrollData.scrollPosition->y / scrollData.contentDimensions.height) * (scrollData.scrollContainerDimensions.height-12);
    CLAY(CLAY_ID("FeatureBlocksOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0f) } })) {
        static char temp[256] = {0};
        memset(temp,0,256);
        snprintf(temp,256,"y: %f",lerpValue);//;
        // CLAY_TEXT(CLAY_STRING(temp), &headerTextConfig);
        if(value < 12.0f){
            CLAY(CLAY_ID("ChristianeHero0"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(1.0f)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/clay/images/christiane0.png") }));
        }
        else if(value < 45.0f )
            CLAY(CLAY_ID("ChristianeHero1"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(1.0f)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/clay/images/christiane1.png") }));
        else{
            CLAY(CLAY_ID("ChristianeHero2"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(1.0f)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/clay/images/christiane2.png") }));
        }
    }
}

void FeatureBlocksMobile() {
    CLAY(CLAY_ID("FeatureBlocksInner"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW() } }), CLAY_BORDER({ .betweenChildren = { .width = 2, .color = COLOR_RED } })) {
        Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_RED });
        CLAY(CLAY_ID("HFileBoxOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW() }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {16, 32}, .childGap = 8 })) {
            CLAY(CLAY_ID("HFileIncludeOuter"), CLAY_LAYOUT({ .padding = {8, 4} }), CLAY_RECTANGLE({ .color = COLOR_RED, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                CLAY_TEXT(CLAY_STRING("#include clay.h"), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
            }
            CLAY_TEXT(CLAY_STRING("~2000 lines of C99."), textConfig);
            CLAY_TEXT(CLAY_STRING("Zero dependencies, including no C standard library."), textConfig);
        }
        CLAY(CLAY_ID("BringYourOwnRendererOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW() }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = 16, .y = 32}, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("Renderer agnostic."), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
            CLAY_TEXT(CLAY_STRING("Layout with clay, then render with Raylib, WebGL Canvas or even as HTML."), textConfig);
            CLAY_TEXT(CLAY_STRING("Flexible output for easy compositing in your custom engine or environment."), textConfig);
        }
    }
}

void DeclarativeSyntaxPageDesktop() {
    CLAY(CLAY_ID("PortraitPageDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight * 0.5f }) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = PAGE_PADDING} })) {
        CLAY(CLAY_ID("PortraitPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { 32, 32 }, .childGap = 32 })) {
            CLAY(CLAY_ID("PortraitPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.65f) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                #define PORTRAIT_FONT_SIZE 36
                CLAY_TEXT(CLAY_STRING("Allo toi!"), CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_FONT_SIZE, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_BLACK }));
                CLAY_TEXT(CLAY_STRING("Voici à qui tu as affaire"), CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_FONT_SIZE, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_BLACK }));
                CLAY(CLAY_ID("PortraitSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) } })) {}
                #define PORTRAIT_SMOL_FONT_SIZE 14
                CLAY_TEXT(
                    CLAY_STRING(
                        "Je suis la fille derrière ookee. Une fille rêveuse, voyageuse, souriante, travaillante…\n"
                        "et follement allumée par ce qui est beau et efficace !"
                    ), 
                    CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_SMOL_FONT_SIZE, .fontId = FONT_ID_BODY_36, .textColor = COLOR_GREY })
                );
                CLAY(CLAY_ID("ParagraphSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = PORTRAIT_SMOL_FONT_SIZE }) } })) {}
                // CLAY_TEXT(CLAY_STRING(), CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_SMOL_FONT_SIZE, .fontId = FONT_ID_BODY_36, .textColor = COLOR_GREY }));
                CLAY_TEXT(
                    CLAY_STRING(
                        "Mon créneau: l’image de marque et la communication intégrée. J’aime faire évoluer"
                        " les entreprises et la perception de leur clientèle. Quand je crée, je n’ai qu’une envie:"
                        " surprendre, captiver, convaincre. Bref, savoir oser autant dans le design que dans"
                        " l’approche. Voilà l’idée !"
                    ), 
                    CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_SMOL_FONT_SIZE, .fontId = FONT_ID_BODY_36, .textColor = COLOR_GREY }));
                CLAY_TEXT(
                    CLAY_STRING(
                        "Il n’y a pas de créatifs heureux sans clients satisfaits. Moi je suis comblée, mes"
                        " clients ont le sourire du début à la fin des mandats. Précieux !"
                    ), 
                    CLAY_TEXT_CONFIG({ .fontSize = PORTRAIT_SMOL_FONT_SIZE, .fontId = FONT_ID_BODY_36, .textColor = COLOR_GREY }));
            }
            CLAY(CLAY_ID("PortraitPageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.35f) }, .childAlignment = {.x = CLAY_ALIGN_X_RIGHT} })) {
                CLAY(CLAY_ID("PortraitPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIT({ .min = 248 *0.75f  }),CLAY_SIZING_FIT({ .min = 318 *0.75f }) } }), CLAY_IMAGE({ .sourceDimensions = {248, 318}, .sourceURL = CLAY_STRING("/clay/images/portrait.png") })) {}
            }
        }
    }
}

void DeclarativeSyntaxPageMobile() {
    CLAY(CLAY_ID("SyntaxPageDesktop"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}, .padding = {16, 32}, .childGap = 16 })) {
        CLAY(CLAY_ID("SyntaxPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("Declarative Syntax"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
            CLAY(CLAY_ID("SyntaxSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) } })) {}
            CLAY_TEXT(CLAY_STRING("Flexible and readable declarative syntax with nested UI element hierarchies."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            CLAY_TEXT(CLAY_STRING("Mix elements with standard C code like loops, conditionals and functions."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            CLAY_TEXT(CLAY_STRING("Create your own library of re-usable components from UI primitives like text, images and rectangles."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
        }
        CLAY(CLAY_ID("SyntaxPageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
            CLAY(CLAY_ID("SyntaxPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 568 }) } }), CLAY_IMAGE({ .sourceDimensions = {1136, 1194}, .sourceURL = CLAY_STRING("/clay/images/declarative.png") } )) {}
        }
    }
}

Clay_Color ColorLerp(Clay_Color a, Clay_Color b, float amount) {
    return (Clay_Color) {
        .r = a.r + (b.r - a.r) * amount,
        .g = a.g + (b.g - a.g) * amount,
        .b = a.b + (b.b - a.b) * amount,
        .a = a.a + (b.a - a.a) * amount,
    };
}

Clay_String LOREM_IPSUM_TEXT = CLAY_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

void HighPerformancePageDesktop(float lerpValue) {
    CLAY(CLAY_ID("PerformanceDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = 82, 32}, .childGap = 64 }), CLAY_RECTANGLE({ .color = COLOR_RED })) {
        CLAY(CLAY_ID("PerformanceLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("High Performance"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
            CLAY(CLAY_ID("PerformanceSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) }})) {}
            CLAY_TEXT(CLAY_STRING("Fast enough to recompute your entire UI every frame."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY_TEXT(CLAY_STRING("Small memory footprint (3.5mb default) with static allocation & reuse. No malloc / free."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY_TEXT(CLAY_STRING("Simplify animations and reactive UI design by avoiding the standard performance hacks."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
        }
        CLAY(CLAY_ID("PerformanceRightImageOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.50) }, .childAlignment = {CLAY_ALIGN_X_CENTER} })) {
            CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(400) } }), CLAY_BORDER_ALL({ .width = 2, .color = COLOR_LIGHT })) {
                CLAY(CLAY_ID("AnimationDemoContainerLeft"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.3f + 0.4f * lerpValue), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = {32, 32} }), CLAY_RECTANGLE({ .color = ColorLerp(COLOR_RED, COLOR_ORANGE, lerpValue) })) {
                    CLAY_TEXT(LOREM_IPSUM_TEXT, CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                }
                CLAY(CLAY_ID("AnimationDemoContainerRight"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER},  .padding = {32, 32} }), CLAY_RECTANGLE({ .color = ColorLerp(COLOR_ORANGE, COLOR_RED, lerpValue) })) {
                    CLAY_TEXT(LOREM_IPSUM_TEXT, CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                }
            }
        }
    }
}

void HighPerformancePageMobile(float lerpValue) {
    CLAY(CLAY_ID("PerformanceMobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}, .padding = {.x = 16, 32}, .childGap = 32 }), CLAY_RECTANGLE({ .color = COLOR_RED })) {
        CLAY(CLAY_ID("PerformanceLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("High Performance"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
            CLAY(CLAY_ID("PerformanceSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) }})) {}
            CLAY_TEXT(CLAY_STRING("Fast enough to recompute your entire UI every frame."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY_TEXT(CLAY_STRING("Small memory footprint (3.5mb default) with static allocation & reuse. No malloc / free."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY_TEXT(CLAY_STRING("Simplify animations and reactive UI design by avoiding the standard performance hacks."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
        }
        CLAY(CLAY_ID("PerformanceRightImageOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .childAlignment = {CLAY_ALIGN_X_CENTER} })) {
            CLAY(CLAY_ID(""), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(400) } }), CLAY_BORDER_ALL({ .width = 2, .color = COLOR_LIGHT })) {
                CLAY(CLAY_ID("AnimationDemoContainerLeft"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.35f + 0.3f * lerpValue), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = {16, 16} }), CLAY_RECTANGLE({ .color = ColorLerp(COLOR_RED, COLOR_ORANGE, lerpValue) })) {
                    CLAY_TEXT(LOREM_IPSUM_TEXT, CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                }
                CLAY(CLAY_ID("AnimationDemoContainerRight"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = {16, 16} }), CLAY_RECTANGLE({ .color = ColorLerp(COLOR_ORANGE, COLOR_RED, lerpValue) })) {
                    CLAY_TEXT(LOREM_IPSUM_TEXT, CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                }
            }
        }
    }
}

void HandleRendererButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData) {
    if (pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        ACTIVE_RENDERER_INDEX = (uint32_t)userData;
    }
}

void RendererButtonActive(Clay_String text) {
    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(300) }, .padding = {16, 16} }),
        CLAY_RECTANGLE({ .color = Clay_Hovered() ? COLOR_RED_HOVER : COLOR_RED, .cornerRadius = CLAY_CORNER_RADIUS(10) })
    ) {
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
    }
}

void RendererButtonInactive(Clay_String text, size_t rendererIndex) {
    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(300)}, .padding = {16, 16} }),
        CLAY_BORDER_OUTSIDE_RADIUS(2, COLOR_RED, 10),
        CLAY_RECTANGLE({ .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT, .cornerRadius = CLAY_CORNER_RADIUS(10), .cursorPointer = true }),
        Clay_OnHover(HandleRendererButtonInteraction, rendererIndex)
    ) {
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
    }
}

void RendererPageDesktop() {
    CLAY(CLAY_ID("RendererPageDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = 50} })) {
        CLAY(CLAY_ID("RendererPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { 32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2, COLOR_RED }, .right = { 2, COLOR_RED } })) {
            CLAY(CLAY_ID("RendererLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("Renderer & Platform Agnostic"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                CLAY(CLAY_ID("RendererSpacerLeft"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) }})) {}
                CLAY_TEXT(CLAY_STRING("Clay outputs a sorted array of primitive render commands, such as RECTANGLE, TEXT or IMAGE."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("Write your own renderer in a few hundred lines of code, or use the provided examples for Raylib, WebGL canvas and more."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("There's even an HTML renderer - you're looking at it right now!"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            }
            CLAY(CLAY_ID("RendererRightText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .childAlignment = {CLAY_ALIGN_X_CENTER}, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 16 })) {
                CLAY_TEXT(CLAY_STRING("Try changing renderer!"), CLAY_TEXT_CONFIG({ .fontSize = 36, .fontId = FONT_ID_BODY_36, .textColor = COLOR_ORANGE }));
                CLAY(CLAY_ID("RendererSpacerRight"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 32 }) } })) {}
                if (ACTIVE_RENDERER_INDEX == 0) {
                    RendererButtonActive(CLAY_STRING("HTML Renderer"));
                    RendererButtonInactive(CLAY_STRING("Canvas Renderer"), 1);
                } else {
                    RendererButtonInactive(CLAY_STRING("HTML Renderer"), 0);
                    RendererButtonActive(CLAY_STRING("Canvas Renderer"));
                }
            }
        }
    }
}

void RendererPageMobile() {
    CLAY(CLAY_ID("RendererMobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}, .padding = {.x = 16, 32}, .childGap = 32 }), CLAY_RECTANGLE({ .color = COLOR_LIGHT })) {
        CLAY(CLAY_ID("RendererLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("Renderer & Platform Agnostic"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
            CLAY(CLAY_ID("RendererSpacerLeft"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) }})) {}
            CLAY_TEXT(CLAY_STRING("Clay outputs a sorted array of primitive render commands, such as RECTANGLE, TEXT or IMAGE."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            CLAY_TEXT(CLAY_STRING("Write your own renderer in a few hundred lines of code, or use the provided examples for Raylib, WebGL canvas and more."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            CLAY_TEXT(CLAY_STRING("There's even an HTML renderer - you're looking at it right now!"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
        }
        CLAY(CLAY_ID("RendererRightText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 16 })) {
            CLAY_TEXT(CLAY_STRING("Try changing renderer!"), CLAY_TEXT_CONFIG({ .fontSize = 36, .fontId = FONT_ID_BODY_36, .textColor = COLOR_ORANGE }));
            CLAY(CLAY_ID("RendererSpacerRight"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 32}) }})) {}
            if (ACTIVE_RENDERER_INDEX == 0) {
                RendererButtonActive(CLAY_STRING("HTML Renderer"));
                RendererButtonInactive(CLAY_STRING("Canvas Renderer"), 1);
            } else {
                RendererButtonInactive(CLAY_STRING("HTML Renderer"), 0);
                RendererButtonActive(CLAY_STRING("Canvas Renderer"));
            }
        }
    }
}

void DebuggerPageDesktop() {
    CLAY(CLAY_ID("DebuggerDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight - 50 }) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = 82, 32}, .childGap = 64 }), CLAY_RECTANGLE({ .color = COLOR_RED })) {
        CLAY(CLAY_ID("DebuggerLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
            CLAY_TEXT(CLAY_STRING("Integrated Debug Tools"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
            CLAY(CLAY_ID("DebuggerSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 16 }) }})) {}
            CLAY_TEXT(CLAY_STRING("Clay includes built in \"Chrome Inspector\"-style debug tooling."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY_TEXT(CLAY_STRING("View your layout hierarchy and config in real time."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            CLAY(CLAY_ID("DebuggerPageSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(32) } })) {}
            CLAY_TEXT(CLAY_STRING("Press the \"d\" key to try it out now!"), CLAY_TEXT_CONFIG({ .fontSize = 32, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_ORANGE }));
        }
        CLAY(CLAY_ID("DebuggerRightImageOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.50) }, .childAlignment = {CLAY_ALIGN_X_CENTER} })) {
            CLAY(CLAY_ID("DebuggerPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = 558 }) } }), CLAY_IMAGE({ .sourceDimensions = {1620, 1474}, .sourceURL = CLAY_STRING("/clay/images/debugger.png") })) {}
        }
    }
}

typedef struct
{
    Clay_Vector2 clickOrigin;
    Clay_Vector2 positionOrigin;
    bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = (ScrollbarData) {};
float animationLerpValue = -1.0f;
#define TEXT_COLOR {48, 49, 51, 255}
Clay_RenderCommandArray CreateLayout(bool mobileScreen, float lerpValue) {
    Clay_BeginLayout();
    CLAY(CLAY_ID("OuterContainer"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() } }), CLAY_RECTANGLE({ .color = COLOR_LIGHT })) {
        CLAY(CLAY_ID("Header"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(50) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .childGap = 16, .padding = { 32 } })) {
            CLAY(CLAY_ID("LogoImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(96),CLAY_SIZING_FIXED(32) } }),CLAY_IMAGE({ .sourceDimensions = { 552, 168 }, .sourceURL = CLAY_STRING("/clay/images/ookee.png") }));
            CLAY(CLAY_ID("Spacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
            CLAY(CLAY_ID("LinkContact"), CLAY_LAYOUT({ .padding = {8} }), CLAY_RECTANGLE({ .link = CLAY_STRING("mailto:christiane@ookee.ca"), .color = {0,0,0,0} })) {
                CLAY_TEXT(CLAY_STRING("Me contacter"), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = TEXT_COLOR }));
            }
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(32),CLAY_SIZING_FIXED(32) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.facebook.com/ookeestudio"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("FbImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.75),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 56, 89 }, .sourceURL = CLAY_STRING("/clay/images/Facebook.png") }));
            }
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(32),CLAY_SIZING_FIXED(32) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.instagram.com/kri_ookee/?hl=fr-ca "), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("InstaImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 80, 80 }, .sourceURL = CLAY_STRING("/clay/images/Instagram.png") }));
            }
            
        }
        CLAY(CLAY_ID("OuterScrollContainer"),
            CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM }),
            CLAY_SCROLL({ .vertical = true }),
            CLAY_BORDER({ .betweenChildren = {2, COLOR_BLACK} })
        ) {
            Clay_ScrollContainerData scrollData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
            // if (mobileScreen) {
            //     LandingPageMobile();
            //     FeatureBlocksMobile();
            //     DeclarativeSyntaxPageMobile();
            //     HighPerformancePageMobile(lerpValue);
            //     RendererPageMobile();
            // } else {
                LandingPageDesktop();
                FeatureBlocksDesktop(scrollData,lerpValue);
                DeclarativeSyntaxPageDesktop();
                HighPerformancePageDesktop(lerpValue);
                RendererPageDesktop();
                DebuggerPageDesktop();
            // }
        }
    }

    if (!mobileScreen) {
        Clay_ScrollContainerData scrollData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        Clay_Color scrollbarColor = (Clay_Color){225, 138, 50, 120};
        if (scrollbarData.mouseDown) {
            scrollbarColor = (Clay_Color){225, 138, 50, 200};
        } else if (Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar")))) {
            scrollbarColor = (Clay_Color){225, 138, 50, 160};
        }
        float scrollHeight = scrollData.scrollContainerDimensions.height - 12;
        CLAY(CLAY_ID("ScrollBar"),
            CLAY_FLOATING({ .offset = { .x = -6, .y = -(scrollData.scrollPosition->y / scrollData.contentDimensions.height) * scrollHeight + 6}, .zIndex = 1, .parentId = Clay_GetElementId(CLAY_STRING("OuterScrollContainer")).id, .attachment = {.element = CLAY_ATTACH_POINT_RIGHT_TOP, .parent = CLAY_ATTACH_POINT_RIGHT_TOP }}),
            CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(10), CLAY_SIZING_FIXED((scrollHeight / scrollData.contentDimensions.height) * scrollHeight)} }),
            CLAY_RECTANGLE({ .cornerRadius = CLAY_CORNER_RADIUS(5), .color = scrollbarColor })
        ) {}
    }
    return Clay_EndLayout();
}

bool debugModeEnabled = false;

CLAY_WASM_EXPORT("UpdateDrawFrame") Clay_RenderCommandArray UpdateDrawFrame(float width, float height, float mouseWheelX, float mouseWheelY, float mousePositionX, float mousePositionY, bool isTouchDown, bool isMouseDown, bool arrowKeyDownPressedThisFrame, bool arrowKeyUpPressedThisFrame, bool dKeyPressedThisFrame, float deltaTime) {
    windowWidth = width;
    windowHeight = height;
    PAGE_PADDING = windowWidth *0.05f;
    Clay_SetLayoutDimensions((Clay_Dimensions) { width, height });
    if (deltaTime == deltaTime) { // NaN propagation can cause pain here
        animationLerpValue += deltaTime;
        if (animationLerpValue > 1) {
            animationLerpValue -= 2;
        }
    }

    if (dKeyPressedThisFrame) {
        debugModeEnabled = !debugModeEnabled;
        Clay_SetDebugModeEnabled(debugModeEnabled);
    }

    Clay__debugViewHighlightColor = (Clay_Color) {105,210,231, 120};

    Clay_SetPointerState((Clay_Vector2) {mousePositionX, mousePositionY}, isMouseDown || isTouchDown);

    if (!isMouseDown) {
        scrollbarData.mouseDown = false;
    }

    if (isMouseDown && !scrollbarData.mouseDown && Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar")))) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        scrollbarData.clickOrigin = (Clay_Vector2) { mousePositionX, mousePositionY };
        scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
        scrollbarData.mouseDown = true;
    } else if (scrollbarData.mouseDown) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            Clay_Vector2 ratio = (Clay_Vector2) {
                scrollContainerData.contentDimensions.width / scrollContainerData.scrollContainerDimensions.width,
                scrollContainerData.contentDimensions.height / scrollContainerData.scrollContainerDimensions.height,
            };
            if (scrollContainerData.config.vertical) {
                scrollContainerData.scrollPosition->y = scrollbarData.positionOrigin.y + (scrollbarData.clickOrigin.y - mousePositionY) * ratio.y;
            }
            if (scrollContainerData.config.horizontal) {
                scrollContainerData.scrollPosition->x = scrollbarData.positionOrigin.x + (scrollbarData.clickOrigin.x - mousePositionX) * ratio.x;
            }
        }
    }

    if (arrowKeyDownPressedThisFrame) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y - 50;
        }
    } else if (arrowKeyUpPressedThisFrame) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        if (scrollContainerData.contentDimensions.height > 0) {
            scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y + 50;
        }
    }

    Clay_UpdateScrollContainers(isTouchDown, (Clay_Vector2) {mouseWheelX, mouseWheelY}, deltaTime);
    bool isMobileScreen = windowWidth < 750;
    if (debugModeEnabled) {
        isMobileScreen = windowWidth < 950;
    }
    return CreateLayout(isMobileScreen, animationLerpValue < 0 ? (animationLerpValue + 1) : (1 - animationLerpValue));
    //----------------------------------------------------------------------------------
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this example
int main() {
    return 0;
}