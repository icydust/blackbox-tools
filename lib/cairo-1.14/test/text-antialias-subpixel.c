/*
 * Copyright © 2005 Red Hat, Inc.
 * Copyright © 2011 Uli Schlachter
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Red Hat, Inc. not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. Red Hat, Inc. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * RED HAT, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL RED HAT, INC. BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: Uli Schlachter <psychon@znc.in>
 *
 * Based on test/text-antialias.c
 * Author: Carl D. Worth <cworth@cworth.org>
 */

#include "../../cairo-1.14/test/cairo-test.h"

#define WIDTH  31
#define HEIGHT 22
#define TEXT_SIZE 12

static cairo_test_status_t
draw (cairo_t *cr, cairo_subpixel_order_t order)
{
    cairo_text_extents_t extents;
    cairo_font_options_t *font_options;
    const char black[] = "black", blue[] = "blue";

    cairo_set_source_rgb (cr, 1.0, 1.0, 1.0); /* white */
    cairo_paint (cr);

    cairo_select_font_face (cr, CAIRO_TEST_FONT_FAMILY " Sans",
			    CAIRO_FONT_SLANT_NORMAL,
			    CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, TEXT_SIZE);

    font_options = cairo_font_options_create ();
    cairo_get_font_options (cr, font_options);
    cairo_font_options_set_antialias (font_options, CAIRO_ANTIALIAS_SUBPIXEL);
    cairo_font_options_set_subpixel_order (font_options, order);
    cairo_set_font_options (cr, font_options);

    cairo_font_options_destroy (font_options);

    cairo_set_source_rgb (cr, 0, 0, 0); /* black */
    cairo_text_extents (cr, black, &extents);
    cairo_move_to (cr, -extents.x_bearing, -extents.y_bearing);
    cairo_show_text (cr, black);
    cairo_translate (cr, 0, -extents.y_bearing + 1);

    cairo_set_source_rgb (cr, 0, 0, 1); /* blue */
    cairo_text_extents (cr, blue, &extents);
    cairo_move_to (cr, -extents.x_bearing, -extents.y_bearing);
    cairo_show_text (cr, blue);

    return CAIRO_TEST_SUCCESS;
}

static cairo_test_status_t
draw_rgb (cairo_t *cr, int width, int height)
{
    return draw (cr, CAIRO_SUBPIXEL_ORDER_RGB);
}

static cairo_test_status_t
draw_bgr (cairo_t *cr, int width, int height)
{
    return draw (cr, CAIRO_SUBPIXEL_ORDER_BGR);
}

static cairo_test_status_t
draw_vrgb (cairo_t *cr, int width, int height)
{
    return draw (cr, CAIRO_SUBPIXEL_ORDER_VRGB);
}

static cairo_test_status_t
draw_vbgr (cairo_t *cr, int width, int height)
{
    return draw (cr, CAIRO_SUBPIXEL_ORDER_VBGR);
}

CAIRO_TEST (text_antialias_subpixel_rgb,
	    "Tests text rendering with rgb subpixel antialiasing",
	    "text", /* keywords */
	    "target=raster", /* requirements */
	    WIDTH, HEIGHT,
	    NULL, draw_rgb)

CAIRO_TEST (text_antialias_subpixel_bgr,
	    "Tests text rendering with bgr subpixel antialiasing",
	    "text", /* keywords */
	    "target=raster", /* requirements */
	    WIDTH, HEIGHT,
	    NULL, draw_bgr)

CAIRO_TEST (text_antialias_subpixel_vrgb,
	    "Tests text rendering with vertical rgb subpixel antialiasing",
	    "text", /* keywords */
	    "target=raster", /* requirements */
	    WIDTH, HEIGHT,
	    NULL, draw_vrgb)

CAIRO_TEST (text_antialias_subpixel_vbgr,
	    "Tests text rendering with vertical bgr subpixel antialiasing",
	    "text", /* keywords */
	    "target=raster", /* requirements */
	    WIDTH, HEIGHT,
	    NULL, draw_vbgr)