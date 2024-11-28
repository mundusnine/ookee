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
const Clay_Color COLOR_WHITE_GREY = (Clay_Color) {244,244,244, 255};


#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) (Clay_Vector2) { .x = (vector).x, .y = (vector).y }

Clay_TextElementConfig headerTextConfig = (Clay_TextElementConfig) { .fontId = 2, .fontSize = 24, .textColor = {61, 26, 5, 255} };
Clay_TextElementConfig blobTextConfig = (Clay_TextElementConfig) { .fontId = 2, .fontSize = 30, .textColor = {244, 235, 230, 255} };
static float scroll_value = 0.0f;

void LandingPageDesktop(Clay_TextElementConfig * big_font,Clay_TextElementConfig * smol_font,Clay_SizingAxis logo_size) {
    CLAY(CLAY_ID("LandingPage1Desktop"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT({ .min = windowHeight * 0.25f }) }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}})) {
        CLAY(CLAY_ID("LandingPage1"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = { PAGE_PADDING, PAGE_PADDING }, .childGap = 32 }), CLAY_BORDER({ .left = { 2 }, .right = { 2 } })) {
            CLAY(CLAY_ID("LeftText"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(0.60f) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8, .padding = { .x=PAGE_PADDING} })) {
                CLAY_TEXT(CLAY_STRING("Designer graphique, DA & DC"), smol_font);
                CLAY_TEXT(CLAY_STRING("C’est bien moi — "), big_font);
                CLAY_TEXT(CLAY_STRING("Christiane"), big_font);
                CLAY_TEXT(CLAY_STRING("Bienvenue dans mon studio"), smol_font);
            }
            CLAY(CLAY_ID("HeroImageOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_PERCENT(0.37f) }, .childAlignment = { CLAY_ALIGN_X_RIGHT } })) {
                CLAY(CLAY_ID("HeroSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
                CLAY(CLAY_ID("RotateLogo"), CLAY_LAYOUT({ .sizing = { logo_size } }),CLAY_IMAGE({ .sourceDimensions = { 636, 636 }, .sourceURL = CLAY_STRING("/ookee/images/ookee_Favicon.png") }));
            }
        }
    }
}

void FeatureBlocks(Clay_ScrollContainerData scrollData,int isMobile,float lerpValue) {
    CLAY(CLAY_ID("FeatureBlocksOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0f) } })) {
        static char temp[256] = {0};
        memset(temp,0,256);
        snprintf(temp,256,"y: %f",lerpValue);//;
        // CLAY_TEXT(CLAY_STRING(temp), &headerTextConfig);
        float values[2] = {scrollData.contentDimensions.height *0.0005,scrollData.contentDimensions.height*0.002};
        if(isMobile){

        }
        if(scroll_value < values[0]){
            CLAY(CLAY_ID("ChristianeHero0"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_FIXED(windowWidth)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/ookee/images/christiane0.png") }));
        }
        else if(scroll_value < values[1] )
            CLAY(CLAY_ID("ChristianeHero1"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_FIXED(windowWidth)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/ookee/images/christiane1.png") }));
        else{
            CLAY(CLAY_ID("ChristianeHero2"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_FIXED(windowWidth)} }),CLAY_IMAGE({ .sourceDimensions = { 1280, 853 }, .sourceURL = CLAY_STRING("/ookee/images/christiane2.png") }));
        }
    }
}

const Clay_String portraits[] = {
    CLAY_STRING("/ookee/images/portrait0.png"),
    CLAY_STRING("/ookee/images/portrait1.png"),
    CLAY_STRING("/ookee/images/portrait2.png"),
    CLAY_STRING("/ookee/images/portrait3.png"),
    CLAY_STRING("/ookee/images/portrait4.png"),
    CLAY_STRING("/ookee/images/portrait5.png"),
    CLAY_STRING("/ookee/images/portrait6.png")
};
const size_t portraits_num = sizeof(portraits)/sizeof(portraits[0]);
void PortraitPage(int isMobile,float lerpValue) {
    CLAY(CLAY_ID("PortraitPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIT({ .min = windowHeight * 0.5f }) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {.x = PAGE_PADDING} })) {
        CLAY(CLAY_ID("PortraitPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { .x=PAGE_PADDING}, .childGap = 32 })) {
            CLAY(CLAY_ID("PortraitPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.65f) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8})) {
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
                //@TODO: Add animation
                float scroll_amount = isMobile ? windowHeight * 0.1f : windowHeight * 0.25f;
                int portrait_idx =  scroll_value >= scroll_amount ? portraits_num-1 : 0;
                CLAY(CLAY_ID("PortraitPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIT({ .min = 248 *0.75f  }),CLAY_SIZING_FIT({ .min = 318 *0.75f }) } }), CLAY_IMAGE({ .sourceDimensions = {248, 318}, .sourceURL = portraits[portrait_idx] })) {}
            }
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

void GalleryPageBlob(int index,Clay_Color color, Clay_String imageURL) {
    CLAY(CLAY_IDI("HeroBlob", index), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.325) } })) {
        CLAY(CLAY_IDI("Gallery", index), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0) } }), CLAY_BORDER_OUTSIDE_RADIUS(2, color, 10), CLAY_IMAGE({ .sourceDimensions = { 1080, 1080 }, .sourceURL = imageURL })) {}
    }

}

#define IMG_PATH "/ookee/images/insta/"
#include "insta_images.c"

void SeeMoarButton(Clay_String text) {
    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(windowWidth * 0.33f * 0.5f) }, .padding = {16, 16},.childAlignment = { CLAY_ALIGN_X_CENTER } }),
        CLAY_RECTANGLE({.link = CLAY_STRING("https://www.instagram.com/kri_ookee/?hl=fr-ca"), .color = Clay_Hovered() ? COLOR_GREY : COLOR_BLACK, .cornerRadius = CLAY_CORNER_RADIUS(10) })
    ) {
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontSize = 16, .fontId = FONT_ID_BODY_36, .textColor = COLOR_WHITE }));
    }
}
Clay_String partners[] = {
    CLAY_STRING("Passion Jardins"),
    CLAY_STRING("Infinima"),
    CLAY_STRING("Monastère des Augustines"),
    CLAY_STRING("Nourcy"),
    CLAY_STRING("Promutuel"),
    CLAY_STRING("Maître Paysagiste"),
    CLAY_STRING("Radiologie lévis"),
    CLAY_STRING("La Boîte à Pain"),
    CLAY_STRING("Yellow Brick"),
    CLAY_STRING("Il Matto"),
    CLAY_STRING("Groupex"),
    CLAY_STRING("Fémina"),
    CLAY_STRING("Commissaire à la langue française"),
    CLAY_STRING("Fondation de l’Hôpital Sainte-Anne de Beaupré")
};
// const size_t partners_size = sizeof(partners)/sizeof(partners[0]);
// #define SEPARATOR CLAY_STRING("  ·  ")
// void carrousel(void){
//     CLAY(CLAY_ID("CarrouselScrollContainer"),
//             CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(windowWidth*0.75f), CLAY_SIZING_GROW() }, .layoutDirection = CLAY_LEFT_TO_RIGHT }),
//             CLAY_SCROLL({ .horizontal = true })
//         ) {
//         CLAY(CLAY_ID("TestPageDesktop"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_FIXED(windowWidth)}, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}})) {
//             for(int i =0; i < partners_size;++i){
//                 CLAY_TEXT(partners[i], CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = COLOR_BLACK }));
//                 CLAY_TEXT(SEPARATOR, CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = COLOR_BLACK }));
//             }
//         }
//     }
// }
void PortfolioPageDesktop(float lerpValue) {
    Clay_Color bg_color = COLOR_WHITE_GREY;
    #define GALLERY_GAP 2
    CLAY(CLAY_ID("GalleryImageOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_GROW() }, .childAlignment = { CLAY_ALIGN_X_CENTER }, .childGap = GALLERY_GAP }),CLAY_RECTANGLE({ .color = bg_color })) {
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 48, .textColor = COLOR_BLACK }));
        CLAY(CLAY_ID("PortfolioTitle"), CLAY_LAYOUT({ .layoutDirection = CLAY_LEFT_TO_RIGHT, .sizing = { .width = CLAY_SIZING_GROW() }, .childAlignment = { CLAY_ALIGN_X_CENTER }, .childGap = GALLERY_GAP,.padding = { .x=PAGE_PADDING * 1.75 } }),CLAY_RECTANGLE({ .color = bg_color })) {
            CLAY_TEXT(CLAY_STRING("Mes réalisations"), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 26, .textColor = COLOR_BLACK }));
            CLAY(CLAY_ID("PortfolioSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
            CLAY(CLAY_ID("PortfolioDescription"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_PERCENT(0.5) }, .childAlignment = { CLAY_ALIGN_X_RIGHT }, .childGap = 4 }),CLAY_RECTANGLE({ .color = bg_color })) {
                CLAY_TEXT(CLAY_STRING("Voilà un petit survol de mes derniers projets réalisés."), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 11, .textColor = COLOR_GREY }));
                CLAY_TEXT(CLAY_STRING("Vous y trouverez toute la diversité qui fait mon quotidien."), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 11, .textColor = COLOR_GREY }));
            }
            
        }
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = COLOR_BLACK }));
        // CLAY(CLAY_ID("GallerySpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIT({ .min = PAGE_PADDING * 2 }) } })) {}
        for(int i =0; i < NUM_IMGS;){
            CLAY(CLAY_IDI("GalleryImageInner",i), CLAY_LAYOUT({ .layoutDirection = CLAY_LEFT_TO_RIGHT, .sizing = { .width = CLAY_SIZING_FIT({ .min = windowWidth - PAGE_PADDING })},.childGap = GALLERY_GAP, .childAlignment = { CLAY_ALIGN_X_CENTER },.padding = { .x=PAGE_PADDING } })) {
                for(int y = 0;y < 3;++y){
                    GalleryPageBlob(i,bg_color,image_names[i]);
                    ++i;
                }
            }
        }
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = COLOR_BLACK }));
        SeeMoarButton(CLAY_STRING("En voir plus"));
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 48, .textColor = COLOR_BLACK }));
    }
}

void PortfolioPageMobile(float lerpValue) {

}

void Footer() {
    CLAY(CLAY_ID("FooterOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_GROW() }, .childAlignment = { CLAY_ALIGN_X_LEFT }, .childGap = GALLERY_GAP }),CLAY_RECTANGLE({ .color = COLOR_WHITE })) {
        const float PAD = PAGE_PADDING * 0.33f;
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = PAD, .textColor = COLOR_BLACK }));
        CLAY(CLAY_ID("FooterTop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(60) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .childGap = 16, .padding = { PAGE_PADDING * 0.5f } })) {
            CLAY(CLAY_ID("FLogoImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(96),CLAY_SIZING_FIXED(32) } }),CLAY_IMAGE({ .sourceDimensions = { 552, 168 }, .sourceURL = CLAY_STRING("/ookee/images/ookee.png") }));
            CLAY(CLAY_ID("FHeadSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
            const int icon_size = 20;
            CLAY(CLAY_ID("FLinkContact"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_FIXED(96) } }), CLAY_RECTANGLE({ .link = CLAY_STRING("mailto:christiane@ookee.ca"), .color = {0,0,0,0} })) {
                CLAY_TEXT(CLAY_STRING("Me contacter"), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = icon_size, .textColor = COLOR_BLACK }));
            }
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(icon_size) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.facebook.com/ookeestudio"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("FFbImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.75),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 56, 89 }, .sourceURL = CLAY_STRING("/ookee/images/Facebook.png") }));
            }
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(icon_size) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.instagram.com/kri_ookee/?hl=fr-ca"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("FInstaImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 80, 80 }, .sourceURL = CLAY_STRING("/ookee/images/Instagram.png") }));
            }
            
        }
        CLAY(CLAY_ID("FooterBott"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW() }, .padding = { .x=PAGE_PADDING * 0.5f } })) {
            CLAY_TEXT(CLAY_STRING("© 2025 Ookee — Le studio de Kristiane. Tous droits réservés."), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = COLOR_BLACK }));
        }
        CLAY_TEXT(CLAY_STRING(" "), CLAY_TEXT_CONFIG({ .fontId = FONT_ID_BODY_24, .fontSize = PAD, .textColor = COLOR_BLACK }));
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
            CLAY(CLAY_ID("LogoImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(96),CLAY_SIZING_FIXED(32) } }),CLAY_IMAGE({ .sourceDimensions = { 552, 168 }, .sourceURL = CLAY_STRING("/ookee/images/ookee.png") }));
            CLAY(CLAY_ID("HeadSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })) {}
            #define ICON_SIZES 24
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(ICON_SIZES),CLAY_SIZING_FIXED(ICON_SIZES) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.facebook.com/ookeestudio"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("FbImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.75),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 56, 89 }, .sourceURL = CLAY_STRING("/ookee/images/Facebook.png") }));
            }
            CLAY(
                CLAY_LAYOUT(
                    { .sizing = { CLAY_SIZING_FIXED(ICON_SIZES),CLAY_SIZING_FIXED(ICON_SIZES) } }
                ),
                CLAY_RECTANGLE({.link = CLAY_STRING("https://www.instagram.com/kri_ookee/?hl=fr-ca"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT })
            ){
                CLAY(CLAY_ID("InstaImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(1.0),CLAY_SIZING_PERCENT(1.0) } }),CLAY_IMAGE({ .sourceDimensions = { 80, 80 }, .sourceURL = CLAY_STRING("/ookee/images/Instagram.png") }));
            }
            
        }
        // carrousel();
        CLAY(CLAY_ID("OuterScrollContainer"),
            CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }, .layoutDirection = CLAY_TOP_TO_BOTTOM }),
            CLAY_SCROLL({ .vertical = true })
        ) {
            Clay_ScrollContainerData scrollData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
            scroll_value = -(scrollData.scrollPosition->y / scrollData.contentDimensions.height) * (scrollData.scrollContainerDimensions.height-12);
            if(mobileScreen){
                const Clay_TextElementConfig * mob_big = CLAY_TEXT_CONFIG({.fontSize = 36,.fontId = FONT_ID_TITLE_56,.textColor = COLOR_BLACK });
                const Clay_TextElementConfig * mob_smol = CLAY_TEXT_CONFIG({ .fontSize = 16, .fontId = FONT_ID_TITLE_36,.textColor = COLOR_BLACK});
                Clay_SizingAxis mob_size = CLAY_SIZING_FIT({ .min = windowHeight * 0.15f });
                LandingPageDesktop((Clay_TextElementConfig *)mob_big,(Clay_TextElementConfig *)mob_smol,mob_size);
            }
            else {
                const Clay_TextElementConfig * big = CLAY_TEXT_CONFIG({.fontSize = 72,.fontId = FONT_ID_TITLE_56,.textColor = COLOR_BLACK });
                const Clay_TextElementConfig * smol = CLAY_TEXT_CONFIG({ .fontSize = 26, .fontId = FONT_ID_TITLE_36,.textColor = COLOR_BLACK});
                Clay_SizingAxis size = CLAY_SIZING_FIT({ .min = windowHeight * 0.25f });
                LandingPageDesktop((Clay_TextElementConfig *)big,(Clay_TextElementConfig *)smol,size);
            }
            FeatureBlocks(scrollData,mobileScreen,lerpValue);
            PortraitPage(mobileScreen,lerpValue);
            PortfolioPageDesktop(lerpValue);
            Footer();
            
        }
    }
    CLAY(CLAY_ID("LinkContact"), 
        CLAY_FLOATING({ .offset = { .x = -windowWidth * 0.01f, .y = 100}, .zIndex = 1, .parentId = Clay_GetElementId(CLAY_STRING("Header")).id, .attachment = {.element = CLAY_ATTACH_POINT_LEFT_BOTTOM, .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM }}),
        CLAY_LAYOUT({ .padding = {8} }), 
        CLAY_RECTANGLE({ .link = CLAY_STRING("mailto:christiane@ookee.ca"), .color = {0,0,0,0} })) {
        CLAY_TEXT(CLAY_STRING("Me contacter"), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 16, .textColor = TEXT_COLOR }));
    }

    if (!mobileScreen) {
        Clay_ScrollContainerData scrollData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
        Clay_Color scrollbarColor = (Clay_Color){0, 0, 0, 120};
        if (scrollbarData.mouseDown) {
            scrollbarColor = (Clay_Color){0, 0, 0, 200};
        } else if (Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar")))) {
            scrollbarColor = (Clay_Color){0, 0, 0, 160};
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
    // {
    //     //Carrousel Container
    //     Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("CarrouselScrollContainer")));
    //     static float direction_amnt = 100;
    //     if(scrollContainerData.scrollPosition->x > scrollContainerData.scrollContainerDimensions.width || scrollContainerData.scrollPosition->x < 0){
    //         direction_amnt = -direction_amnt;
    //     }
    //     scrollContainerData.scrollPosition->x += direction_amnt * deltaTime;
    // }


    Clay_UpdateScrollContainers(isTouchDown, (Clay_Vector2) {mouseWheelX, mouseWheelY}, deltaTime);
    bool isMobileScreen = windowWidth < 750;
    if (debugModeEnabled) {
        isMobileScreen = windowWidth < 950;
    }
    PAGE_PADDING = windowWidth *0.05f;
    return CreateLayout(isMobileScreen, animationLerpValue < 0 ? (animationLerpValue + 1) : (1 - animationLerpValue));
    //----------------------------------------------------------------------------------
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this example
int main() {
    return 0;
}