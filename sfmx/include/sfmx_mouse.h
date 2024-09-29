#ifndef SFMX_MOUSE_H_
#define SFMX_MOUSE_H_

#include "sfmx_vectors.h"
#include "sfmx_render_window.h"

#include <SFML/Window/Mouse.hpp>

namespace sfmx {

class Mouse
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons
    ///
    ////////////////////////////////////////////////////////////
    enum Button
    {
        Left,       //!< The left mouse button
        Right,      //!< The right mouse button
        Middle,     //!< The middle (wheel) mouse button
        XButton1,   //!< The first extra mouse button
        XButton2,   //!< The second extra mouse button

        ButtonCount //!< Keep last -- the total number of mouse buttons
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse wheels
    ///
    ////////////////////////////////////////////////////////////
    enum Wheel
    {
        VerticalWheel,  //!< The vertical mouse wheel
        HorizontalWheel //!< The horizontal mouse wheel
    };

    ////////////////////////////////////////////////////////////
    /// \brief Check if a mouse button is pressed
    ///
    /// \warning Checking the state of buttons Mouse::XButton1 and
    /// Mouse::XButton2 is not supported on Linux with X11.
    ///
    /// \param button Button to check
    ///
    /// \return True if the button is pressed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool IsButtonPressed(Button button);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in desktop coordinates
    ///
    /// This function returns the global position of the mouse
    /// cursor on the desktop.
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static vec2i GetPosition();

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in window coordinates
    ///
    /// This function returns the current position of the mouse
    /// cursor, relative to the given window.
    ///
    /// \param relativeTo Reference window
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static vec2i GetPosition(const RenderWindow& relativeTo);

    ////////////////////////////////////////////////////////////
    /// \brief Set the current position of the mouse in desktop coordinates
    ///
    /// This function sets the global position of the mouse
    /// cursor on the desktop.
    ///
    /// \param position New position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static void SetPosition(const vec2i& position);

    ////////////////////////////////////////////////////////////
    /// \brief Set the current position of the mouse in window coordinates
    ///
    /// This function sets the current position of the mouse
    /// cursor, relative to the given window.
    ///
    /// \param position New position of the mouse
    /// \param relativeTo Reference window
    ///
    ////////////////////////////////////////////////////////////
    static void SetPosition(const vec2i& position, const RenderWindow& relativeTo);
};

}; // namespace


#endif // SFMX_MOUSE_H_
