// screen_print_preview.hpp
#pragma once
#include "gui.hpp"
#include "window_header.hpp"
#include "window_roll_text.hpp"
#include "screen.hpp"
#include "display.h"
#include "gcode_info.hpp"
#include "gcode_description.hpp"
#include "fs_event_autolock.hpp"
#include "static_alocation_ptr.hpp"

class ScreenPrintPreview : public AddSuperWindow<screen_t> {
    constexpr static const char *labelWarning = N_("Warning");

    static constexpr const char *txt_wrong_printer_type = N_("This G-CODE was set up for another printer type.");
    static constexpr const char *txt_wrong_fil_type = N_("This G-CODE was set up for another filament type.");
    static constexpr const char *txt_fil_not_detected = N_("Filament not detected. Load filament now? Select NO to cancel, or IGNORE to disable the filament sensor and continue.");
    static constexpr const char *txt_fil_detected_mmu = N_("Filament detected. Unload filament now? Select NO to cancel.");

    static ScreenPrintPreview *ths; // to be accessible in dialog handler

    window_roll_text_t title_text;

    GCodeInfo &gcode;
    GCodeInfoWithDescription gcode_description; // cannot be first
    WindowPreviewThumbnail thumbnail;           // draws preview png

    RadioButton radio; // shows 2 mutually exclusive buttons Print and Back

    PhasesPrintPreview phase;

    using UniquePtr = static_unique_ptr<MsgBoxTitled>;
    UniquePtr pMsgbox;

    using MsgBoxMemSpace = std::aligned_union<0, MsgBoxTitled>::type;
    MsgBoxMemSpace msgBoxMemSpace;

    UniquePtr makeMsgBox(const PhaseResponses &resp, string_view_utf8 caption, string_view_utf8 text);

public:
    ScreenPrintPreview();
    virtual ~ScreenPrintPreview() override;
    static ScreenPrintPreview *GetInstance();
    void Change(fsm::BaseData data);

protected:
    virtual void windowEvent(EventLock /*has private ctor*/, window_t *sender, GUI_event_t event, void *param) override;
};
