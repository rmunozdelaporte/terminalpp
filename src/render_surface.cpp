#include "terminalpp/render_surface.hpp"
#include "terminalpp/canvas.hpp"

namespace terminalpp {
namespace {

// ==========================================================================
// DEFAULT RENDER SURFACE CAPABILITIES
// ==========================================================================
class default_render_surface_capabilities
  : public render_surface_capabilities
{
public :
    // ======================================================================
    // SUPPORTS_UNICODE
    // ======================================================================
    bool supports_unicode() const override
    {
        return true;
    }
};

static default_render_surface_capabilities default_capabilities;

}

// ==========================================================================
// ROW_PROXY::CONSTRUCTOR
// ==========================================================================
render_surface::row_proxy::row_proxy(
    render_surface& cvs, coordinate_type column, coordinate_type row)
  : canvas_(cvs),
    column_(column),
    row_(row)
{
}

// ==========================================================================
// ROW_PROXY::OPERATOR=
// ==========================================================================
render_surface::row_proxy &render_surface::row_proxy::operator=(
    render_surface::row_proxy const &other)
{
    canvas_.set_element(column_, row_, other);
    return *this;
}

// ==========================================================================
// ROW_PROXY::OPERATOR=
// ==========================================================================
render_surface::row_proxy &render_surface::row_proxy::operator=(
    element const &value)
{
    canvas_.set_element(column_, row_, value);
    return *this;
}

// ==========================================================================
// ROW_PROXY::CONVERSION OPERATOR
// ==========================================================================
render_surface::row_proxy::operator element &()
{
    return canvas_.get_element(column_, row_);
}

// ==========================================================================
// ROW_PROXY::CONVERSION OPERATOR
// ==========================================================================
render_surface::row_proxy::operator element const &() const
{
    return canvas_.get_element(column_, row_);
}

// ==========================================================================
// COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
render_surface::column_proxy::column_proxy(
    render_surface &cvs, coordinate_type column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// COLUMN_PROXY::OPERATOR[]
// ==========================================================================
render_surface::row_proxy render_surface::column_proxy::operator[](
    coordinate_type row)
{
    return render_surface::row_proxy(canvas_, column_, row);
}

// ==========================================================================
// CONST_COLUMN_PROXY::CONSTRUCTOR
// ==========================================================================
render_surface::const_column_proxy::const_column_proxy(
    render_surface const &cvs, coordinate_type column)
  : canvas_(cvs),
    column_(column)
{
}

// ==========================================================================
// CONST_COLUMN_PROXY::OPERATOR[]
// ==========================================================================
element const &render_surface::const_column_proxy::operator[](
    coordinate_type row) const
{
    return canvas_.get_element(column_, row);
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
render_surface::render_surface(canvas &cvs)
  : render_surface(cvs, default_capabilities)
{
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
render_surface::render_surface(
    canvas &cvs,
    render_surface_capabilities const &capabilities)
  : canvas_(cvs),
    capabilities_(capabilities)
{
}

// ==========================================================================
// SUPPORTS_UNICODE
// ==========================================================================
bool render_surface::supports_unicode() const
{
    return capabilities_.supports_unicode();
}

// ==========================================================================
// OFFSET_BY
// ==========================================================================
void render_surface::offset_by(extent offset)
{
    offset_ += offset;
}

// ==========================================================================
// SIZE
// ==========================================================================
extent render_surface::size() const
{
    return canvas_.size() - offset_;
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
render_surface::column_proxy render_surface::operator[](coordinate_type column)
{
    return column_proxy(*this, column);
}

// ==========================================================================
// OPERATOR[]
// ==========================================================================
render_surface::const_column_proxy render_surface::operator[](
    coordinate_type column) const
{
    return const_column_proxy(*this, column);
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
element &render_surface::get_element(
    coordinate_type column, coordinate_type row)
{
    return canvas_[column + offset_.width][row + offset_.height];
}

// ==========================================================================
// GET_ELEMENT
// ==========================================================================
element const &render_surface::get_element(
    coordinate_type column, coordinate_type row) const
{
    return canvas_[column + offset_.width][row + offset_.height];
}

// ==========================================================================
// SET_ELEMENT
// ==========================================================================
void render_surface::set_element(
    coordinate_type column, coordinate_type row, element const &value)
{
    canvas_[column + offset_.width][row + offset_.height] = value;
}

// ==========================================================================
// OPERATOR<<(row_proxy)
// ==========================================================================
std::ostream &operator<<(
    std::ostream &out,
    render_surface::row_proxy const &row)
{
    return out << terminalpp::element(row);
}

}