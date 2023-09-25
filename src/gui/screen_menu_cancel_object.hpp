/**
 * @file screen_menu_cancel_object.hpp
 */

#pragma once

#include "screen_menu.hpp"
#include "WindowMenuItems.hpp"
#include "MItem_tools.hpp"
#include <marlin_vars.hpp>

#if ENABLED(CANCEL_OBJECTS)

/**
 * @brief Prototype object that can hide functionality in .cpp.
 */
class MI_CO_OBJECT_N : public WI_SWITCH_t<2> {
    char label_buffer[marlin_vars_t::CANCEL_OBJECT_NAME_LEN] = {}; ///< Buffer for object name, start empty

    /// True if object name form G-code is valid, false if backup_label is used or if object name changed
    bool backup_label_used = false; ///< Write backup on first call to UpdateName()
    constexpr static const char *backup_label = N_("Object %i"); ///< "Object <number>", needs to have exactly one "%i" in it

    constexpr static const char *str_printing = N_("Printing"); ///< Object is being printed as normal
    constexpr static const char *str_canceled = N_("Canceled"); ///< Object was canceled and is skipped during print

    const int ObjectId; ///< Id of object to cancel with this switch

public:
    MI_CO_OBJECT_N(int ObjectId_);

    /**
     * @brief Update state of switch.
     */
    void UpdateState();

    /**
     * @brief Update visibility and object name.
     */
    void UpdateName();

protected:
    virtual void OnChange(size_t old_index) override;
};

/**
 * @brief Final template to cancel one object.
 */
template <int ObjectIdN>
class MI_CO_OBJECT : public MI_CO_OBJECT_N {
    static_assert(ObjectIdN < marlin_vars_t::CANCEL_OBJECTS_NAME_COUNT, "Too many objects to cancel!");

public:
    MI_CO_OBJECT()
        : MI_CO_OBJECT_N(ObjectIdN) {}
};

/**
 * @brief Button to cancel current object.
 */
class MI_CO_CANCEL_CURRENT : public WI_LABEL_t {
    static constexpr const char *label = N_("Cancel Current");

public:
    MI_CO_CANCEL_CURRENT();

protected:
    virtual void click(IWindowMenu &window_menu) override;
};

namespace detail {
using ScreenMenuCancelObject = ScreenMenu<GuiDefaults::MenuFooter, MI_RETURN, MI_CO_CANCEL_CURRENT,
    MI_CO_OBJECT<0>,
    MI_CO_OBJECT<1>,
    MI_CO_OBJECT<2>,
    MI_CO_OBJECT<3>,
    MI_CO_OBJECT<4>,
    MI_CO_OBJECT<5>,
    MI_CO_OBJECT<6>,
    MI_CO_OBJECT<7>,
    MI_CO_OBJECT<8>,
    MI_CO_OBJECT<9>,
    MI_CO_OBJECT<10>,
    MI_CO_OBJECT<11>,
    MI_CO_OBJECT<12>,
    MI_CO_OBJECT<13>,
    MI_CO_OBJECT<14>,
    MI_CO_OBJECT<15>>;
} // namespace detail

class ScreenMenuCancelObject : public detail::ScreenMenuCancelObject {
    int loop_index = 0; ///< Refresh names only once every few loops

    /**
     * @brief Periodically unblock button, in case object state does not change after click.
     */
    void Unblock();

public:
    constexpr static const char *label = "Canceled Objects";
    ScreenMenuCancelObject();

protected:
    void windowEvent(EventLock /*has private ctor*/, [[maybe_unused]] window_t *sender, GUI_event_t event, [[maybe_unused]] void *param) override {
        if (event == GUI_event_t::LOOP) {
            if (loop_index++ > 20) { // Approx once a second
                loop_index = 0;
                // Update all object names and visibility
                Item<MI_CO_OBJECT<0>>().UpdateName();
                Item<MI_CO_OBJECT<1>>().UpdateName();
                Item<MI_CO_OBJECT<2>>().UpdateName();
                Item<MI_CO_OBJECT<3>>().UpdateName();
                Item<MI_CO_OBJECT<4>>().UpdateName();
                Item<MI_CO_OBJECT<5>>().UpdateName();
                Item<MI_CO_OBJECT<6>>().UpdateName();
                Item<MI_CO_OBJECT<7>>().UpdateName();
                Item<MI_CO_OBJECT<8>>().UpdateName();
                Item<MI_CO_OBJECT<9>>().UpdateName();
                Item<MI_CO_OBJECT<10>>().UpdateName();
                Item<MI_CO_OBJECT<11>>().UpdateName();
                Item<MI_CO_OBJECT<12>>().UpdateName();
                Item<MI_CO_OBJECT<13>>().UpdateName();
                Item<MI_CO_OBJECT<14>>().UpdateName();
                Item<MI_CO_OBJECT<15>>().UpdateName();

                Unblock(); // Allow button press once a second
            }
            // Update state of all items
            Item<MI_CO_OBJECT<0>>().UpdateState();
            Item<MI_CO_OBJECT<1>>().UpdateState();
            Item<MI_CO_OBJECT<2>>().UpdateState();
            Item<MI_CO_OBJECT<3>>().UpdateState();
            Item<MI_CO_OBJECT<4>>().UpdateState();
            Item<MI_CO_OBJECT<5>>().UpdateState();
            Item<MI_CO_OBJECT<6>>().UpdateState();
            Item<MI_CO_OBJECT<7>>().UpdateState();
            Item<MI_CO_OBJECT<8>>().UpdateState();
            Item<MI_CO_OBJECT<9>>().UpdateState();
            Item<MI_CO_OBJECT<10>>().UpdateState();
            Item<MI_CO_OBJECT<11>>().UpdateState();
            Item<MI_CO_OBJECT<12>>().UpdateState();
            Item<MI_CO_OBJECT<13>>().UpdateState();
            Item<MI_CO_OBJECT<14>>().UpdateState();
            Item<MI_CO_OBJECT<15>>().UpdateState();
        }
    }
};

#else /* ENABLED(CANCEL_OBJECTS) */

class ScreenMenuCancelObject {};

#endif /* ENABLED(CANCEL_OBJECTS) */
