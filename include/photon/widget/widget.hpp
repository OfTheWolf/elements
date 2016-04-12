/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#if !defined(PHOTON_GUI_LIB_WIDGET_APRIL_10_2016)
#define PHOTON_GUI_LIB_WIDGET_APRIL_10_2016

#include <photon/support.hpp>
#include <photon/rect.hpp>
#include <photon/point.hpp>
#include <memory>

namespace photon
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   // widget class
   //
   // This is the class that deals with the graphic representation of fine-grained
   // elements inside a window which may be static images or active controls.
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class widget : public std::enable_shared_from_this<widget>
   {
   public:

      using widget_ptr = std::shared_ptr<widget>;
      using widget_const_ptr = std::shared_ptr<widget const>;

      widget() {}
      ~widget() {}

      widget(widget const&) = delete;
      widget& operator=(widget const&) = delete;

   // image

      virtual rect            limits() const;
      virtual widget*         hit_test(layout_info const& l, point const& p);
      virtual void            draw(layout_info const& l);
      virtual void            layout(rect const& bounds);

   // control

      virtual widget*         click(layout_info const& l, point const& p);
      virtual bool            key(layout_info const& l, key_info const& k);
      virtual bool            cursor(layout_info const& l, point const& p);
      virtual bool            focus(focus_request r);
      virtual widget const*   focus() const;
   };

   using widget_ptr = std::shared_ptr<widget>;
   using widget_const_ptr = std::shared_ptr<widget const>;

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // proxy class
   //
   // A widget that encapsulates another widget. The proxy delegates its methods
   // to an enlosed widget. The proxy acts as a single atomic element instead
   // of a composite.
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class proxy : public widget {

   public:

      proxy(widget_ptr subject_)
       : _subject(subject_) {}
      ~proxy() {}

   // image

      virtual rect            limits() const;
      virtual widget*         hit_test(layout_info const& l, point const& p);
      virtual void            draw(layout_info const& l);
      virtual void            layout(rect const& bounds);
      virtual void            subject_bounds(rect& b);

   // control

      virtual widget*         click(layout_info const& l, point const& p);
      virtual bool            key(layout_info const& l, key_info const& k);
      virtual bool            cursor(layout_info const& l, point const& p);
      virtual bool            focus(focus_request r);
      virtual widget const*   focus() const;

   // proxy

      widget_ptr              subject() const { return _subject; }
      void                    subject(widget_ptr subject_) { _subject = subject_; }

   private:

      widget_ptr              _subject;
   };

}

#endif