#pragma once

#include "terminalpp/render_surface_capabilities.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/extent.hpp"
#include <iosfwd>

namespace terminalpp {

class canvas;

//* =========================================================================
/// \brief A sub-view into a canvas that only allows reading and writing
/// to a its elements; not operations that would affect the entire canvas.
//* =========================================================================
class TERMINALPP_EXPORT render_surface
{
public :
    //* =====================================================================
    /// \brief A proxy into a row of elements on the canvas
    //* =====================================================================
    class row_proxy
    {
    public :
        // ==================================================================
        // CONSTRUCTOR
        // ==================================================================
        row_proxy(
            render_surface &cvs, coordinate_type column, coordinate_type row);

        // ==================================================================
        // OPERATOR=
        // ==================================================================
        row_proxy &operator=(row_proxy const &other);

        // ==================================================================
        // OPERATOR=
        // ==================================================================
        row_proxy &operator=(element const &value);

        // ==================================================================
        // CONVERSION OPERATOR: ELEMENT
        // ==================================================================
        operator element &();

        // ==================================================================
        // CONVERSION OPERATOR: ELEMENT
        // ==================================================================
        operator element const &() const;

    private :
        render_surface &canvas_;
        coordinate_type column_;
        coordinate_type row_;
    };

    //* =====================================================================
    /// \brief A proxy into a column of elements on the canvas
    //* =====================================================================
    class column_proxy
    {
    public :
        // ==================================================================
        // CONSTRUCTOR
        // ==================================================================
        column_proxy(render_surface &cvs, coordinate_type column);

        // ==================================================================
        // OPERATOR[]
        // ==================================================================
        row_proxy operator[](coordinate_type row);

    private :
        render_surface &canvas_;
        coordinate_type column_;
    };

    //* =====================================================================
    /// \brief A constant proxy into a column of elements on the canvas
    //* =====================================================================
    class const_column_proxy
    {
    public :
        // ==================================================================
        // CONSTRUCTOR
        // ==================================================================
        const_column_proxy(render_surface const &cvs, coordinate_type column);

        // ==================================================================
        // OPERATOR[]
        // ==================================================================
        element const &operator[](coordinate_type row) const;

    private :
        render_surface const &canvas_;
        coordinate_type column_;
    };

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit render_surface(canvas &cvs);

    //* =====================================================================
    //\ brief Constructor with explicit render surface capabilities
    //* =====================================================================
    render_surface(
        canvas &cvs,
        render_surface_capabilities const &capabilities);

    //* =====================================================================
    /// \brief Returns true if the surface is known to support unicode.
    /// characters.  Attempting to render unicode on surfaces that do not
    /// support unicode may have unexpected results.
    //* =====================================================================
    bool supports_unicode() const;

    //* =====================================================================
    /// \brief Offsets the canvas by a certain amount, causing it to become
    /// a view with the offset location as a basis.
    //* =====================================================================
    void offset_by(extent offset);

    //* =====================================================================
    /// \brief Returns the size of the canvas.
    //* =====================================================================
    extent size() const;

    //* =====================================================================
    /// \brief A subscript operator into a column
    //* =====================================================================
    column_proxy operator[](coordinate_type column);

    //* =====================================================================
    /// \brief A subscript operator into a column
    //* =====================================================================
    const_column_proxy operator[](coordinate_type column) const;

private :
    //* =====================================================================
    /// \brief Set the value of an element.
    //* =====================================================================
    void set_element(
        coordinate_type column, coordinate_type row, element const &value);

    //* =====================================================================
    /// \brief Get the value of an element.
    //* =====================================================================
    element &get_element(coordinate_type column, coordinate_type row);

    //* =====================================================================
    /// \brief Get the value of an element.
    //* =====================================================================
    element const &get_element(
        coordinate_type column, coordinate_type row) const;

    canvas &canvas_;
    render_surface_capabilities const &capabilities_;
    extent  offset_;
};

TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, render_surface::row_proxy const &row);

}
