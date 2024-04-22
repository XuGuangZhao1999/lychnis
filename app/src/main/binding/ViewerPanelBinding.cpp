#include "main/binding/ViewerPanelBinding.hpp"
#include "shared/AppConfig.hpp"
#include "shared/util/BindingUtil.hpp"

#include <algorithm>
#include <vector>

#include <opencv2/shape/shape_transformer.hpp>

#include "include/cef_parser.h"
#include "include/cef_browser.h"
#include "include/cef_values.h"

namespace app{
    namespace binding{
        ViewerPanelBinding::ViewerPanelBinding(){
            viewer = &VolumeViewer::getInstance();

            tasks.RegisterFunction("mousePressEvent", &ViewerPanelBinding::onTaskMousePressEvent);
            tasks.RegisterFunction("mouseMoveEvent", &ViewerPanelBinding::onTaskMouseMoveEvent);
            tasks.RegisterFunction("mouseReleaseEvent", &ViewerPanelBinding::onTaskMouseReleaseEvent);
            tasks.RegisterFunction("wheelEvent", &ViewerPanelBinding::onTaskWheelEvent);
        }

        bool ViewerPanelBinding::OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t queryId, const CefString &request, bool persistent, CefRefPtr<Callback> callback){
            // Only handle messages from application url
            const std::string &url = frame->GetURL();

            if (!(url.rfind(APP_ORIGIN, 0) == 0))
            {
                return false;
            }

            // Parse request
            auto task = CefParseJSON(request, JSON_PARSER_RFC)->GetDictionary();
            auto func = tasks.GetFunction(task->GetString("functionName"));

            if(nullptr != func){
                auto args = task->GetDictionary("args");
                return (this->*func)(browser, frame, queryId, args, persistent, callback);
            }

            return false;
        }

        bool ViewerPanelBinding::onTaskMousePressEvent(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t queryId, CefRefPtr<CefDictionaryValue> args, bool persistent, CefRefPtr<Callback> callback){
            
            return true;
        }

        bool ViewerPanelBinding::onTaskMouseMoveEvent(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t queryId, CefRefPtr<CefDictionaryValue> args, bool persistent, CefRefPtr<Callback> callback){
            
            return true;
        }

        bool ViewerPanelBinding::onTaskMouseReleaseEvent(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t queryId, CefRefPtr<CefDictionaryValue> args, bool persistent, CefRefPtr<Callback> callback){

            return true;
        }

        bool ViewerPanelBinding::onTaskWheelEvent(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64_t queryId, CefRefPtr<CefDictionaryValue> args, bool persistent, CefRefPtr<Callback> callback){

            return true;
        }
        
        void ViewerPanelBinding::init(CefRefPtr<CefMessageRouterBrowserSide> router){
            router->AddHandler(new ViewerPanelBinding(), false);
        }
    }// namespace binding
}// namespace app