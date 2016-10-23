/*=======================================================================================   Copyright (c) 2016 Joel de Guzman   Distributed under the The MIT License (https://opensource.org/licenses/MIT)
=======================================================================================*/#if !defined(PHOTON_GUI_LIB_CONTEXT_APRIL_17_2016)#define PHOTON_GUI_LIB_CONTEXT_APRIL_17_2016#include <photon/support/point.hpp>#include <photon/support/rect.hpp>#include <cairo.h>namespace photon{	////////////////////////////////////////////////////////////////////////////////////////////////	// Contexts	////////////////////////////////////////////////////////////////////////////////////////////////   class view;   class widget;   class canvas;   struct basic_context   {      basic_context(view& view_, canvas& canvas_)       : view(view_)       , canvas(canvas_)      {}      basic_context(basic_context const&) = default;      basic_context& operator=(basic_context const&) = default;      view&                view;      canvas&              canvas;   };	////////////////////////////////////////////////////////////////////////////////////////////////   struct context : basic_context   {      context(context const& rhs, rect bounds_)       : basic_context(rhs.view, rhs.canvas), widget(rhs.widget)       , parent(rhs.parent), bounds(bounds_)      {}      context(context const& parent_, widget* widget_, rect bounds_)       : basic_context(parent_.view, parent_.canvas), widget(widget_)       , parent(&parent_), bounds(bounds_)      {}      context(class view& view_, class canvas& canvas_, widget* widget_, rect bounds_)       : basic_context(view_, canvas_), widget(widget_)       , parent(0), bounds(bounds_)      {}      context(context const&) = default;      context& operator=(context const&) = default;      widget*              widget;      context const*       parent;      rect                 bounds;   };}#endif