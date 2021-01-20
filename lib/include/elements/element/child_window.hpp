/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_CHILD_WINDOW_JANUARY_19_2021)
#define ELEMENTS_CHILD_WINDOW_JANUARY_19_2021

#include <elements/element/floating.hpp>
#include <elements/element/tracker.hpp>
#include <elements/element/traversal.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Movable: Allows an element (e.g. title_bar) to be movable if it is
   // contained inside a floating_element. The whole floating_element moves
   // when the element is dragged around.
   ////////////////////////////////////////////////////////////////////////////

   struct movable_tracker_info : tracker_info
   {
      using tracker_info::tracker_info;

      float                _offs_top, _offs_bottom;
   };

   class movable_base : public tracker<proxy_base, movable_tracker_info>
   {
   public:

      using tracker = tracker<proxy_base, movable_tracker_info>;

      bool                 click(context const& ctx, mouse_button btn) override;
      void                 drag(context const& ctx, mouse_button btn) override;
      void                 keep_tracking(context const& ctx, tracker_info& track_info) override;
   };

   template <typename Subject>
   inline proxy<remove_cvref_t<Subject>, movable_base>
   movable(Subject&& subject)
   {
      return { std::forward<Subject>(subject) };
   }

   ////////////////////////////////////////////////////////////////////////////
   // Closable: When contained inside a floating_element, allows a button (or
   // any clickable element) to close the floating_element when it is
   // clicked.
   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   class closable_element : public proxy<Subject>
   {
   public:

      using proxy<Subject>::proxy;

      void                    prepare_subject(context& ctx) override;
   };

   template <typename Subject>
   inline closable_element<remove_cvref_t<Subject>>
   closable(Subject&& subject)
   {
      return { std::forward<Subject>(subject) };
   }

   void close_floating_element(context& ctx, floating_element* cw);

   template <typename Subject>
   inline void closable_element<Subject>::prepare_subject(context& ctx)
   {
      this->actual_subject().on_click =
         [&ctx](bool)
         {
            auto fl = find_parent<floating_element*>(ctx);
            if (fl)
              close_floating_element(ctx, fl);
         };
   }
}}

#endif