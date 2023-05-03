// CmakeTest.cpp : Defines the entry point for the application.
//

#include "CmakeTest.h"
#include <iostream>
#include <thread>
#include <vector>
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_handler.h"
#include "include/cef_string_visitor.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include <mutex>

using namespace std;

class HtmlVisitor : public CefStringVisitor {
public:
    HtmlVisitor() = default;

    void Visit(const CefString& string) override {
        std::cout << "HTML content:\n" << string.ToString() << std::endl;
    }

    IMPLEMENT_REFCOUNTING(HtmlVisitor);
};

class SimpleRenderHandler : public CefRenderHandler {
public:
    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override {
        rect = CefRect(0, 0, 1, 1);
        return;
    }

    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override {
        // Nie rób nic, ponieważ nie chcemy wyświetlać zawartości.
    }

    IMPLEMENT_REFCOUNTING(SimpleRenderHandler);
};


class SimpleClient : public CefClient {
public:
    SimpleClient(): renderHandler(new SimpleRenderHandler) {}

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override {
        return renderHandler;
    }

private:
    CefRefPtr<SimpleRenderHandler> renderHandler;

    IMPLEMENT_REFCOUNTING(SimpleClient);
};

class MyLoadHandler : public CefLoadHandler {
public:
    MyLoadHandler() {}

    void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                              bool isLoading,
                              bool canGoBack,
                              bool canGoForward) override {
        // Opcjonalnie: obsługa zmiany stanu ładowania.
    }

    void OnLoadStart(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     TransitionType transition_type) override {
        // Opcjonalnie: obsługa rozpoczęcia ładowania strony.
    }

    void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                   CefRefPtr<CefFrame> frame,
                   int httpStatusCode) override {
        CefRefPtr<HtmlVisitor> html_visitor(new HtmlVisitor);
        browser->GetMainFrame()->GetSource(html_visitor);
        //html_visitor->Visit()
    }

    void OnLoadError(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     ErrorCode errorCode,
                     const CefString& errorText,
                     const CefString& failedUrl) override {
        // Opcjonalnie: obsługa błędów ładowania.
    }

private:
    IMPLEMENT_REFCOUNTING(MyLoadHandler);
};


class MyClient : public CefClient, public CefLifeSpanHandler {
public:
    MyClient():
        renderHandler(new SimpleRenderHandler()),
        loadHandler(new MyLoadHandler()),
        browser_ready_(false),
        browser_closed_(false) {}

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    bool IsBrowserReady() const {
        std::lock_guard<std::mutex> lock(browser_mutex_);
        return browser_ready_;
    }

    bool IsBrowserClosed() const {
        std::lock_guard<std::mutex> lock(browser_mutex_);
        return browser_closed_;
    }

    CefRefPtr<CefBrowser> GetBrowser() const {
        std::lock_guard<std::mutex> lock(browser_mutex_);
        return browser_;
    }


    CefRefPtr<CefLoadHandler> GetLoadHandler() override {
        return loadHandler;
    }

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override {
        return renderHandler;
    }

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        {
            std::lock_guard<std::mutex> lock(browser_mutex_);
            browser_ = browser;
            browser_ready_ = true;
        }
    }

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
        {
            std::lock_guard<std::mutex> lock(browser_mutex_);
            browser_closed_ = true;
        }
    }

private:
    mutable std::mutex browser_mutex_;
    CefRefPtr<CefBrowser> browser_;
    CefRefPtr<SimpleRenderHandler> renderHandler;
    CefRefPtr<MyLoadHandler> loadHandler;
    bool browser_ready_;
    bool browser_closed_;

    IMPLEMENT_REFCOUNTING(MyClient);
    DISALLOW_COPY_AND_ASSIGN(MyClient);
};

void RunBrowser(const std::string& url) {
    //CefRefPtr<CefBrowser> browser;
   // CefRefPtr<SimpleClient> client(new SimpleClient());
    CefRefPtr<MyClient> client(new MyClient());
    CefWindowInfo windowInfo;
    windowInfo.SetAsWindowless(nullptr);

    CefBrowserSettings browserSettings;
    ///browserSettings.

    auto browser = CefBrowserHost::CreateBrowser(windowInfo, client.get(), url, browserSettings, nullptr, nullptr);
    //Oczekuj na zakończenie ładowania strony
//while(browser->IsLoading()) {
//  CefDoMessageLoopWork();
//  std::this_thread::sleep_for(std::chrono::milliseconds(10));
//}

// Odczekaj chwilę, aby strona mogła wykonać JavaScript
//std::this_thread::sleep_for(std::chrono::seconds(5));

//CefRefPtr<GetHtmlSourceTask> task(new GetHtmlSourceTask(browser));
//CefPostTask(TID_UI, task);
///CefRefPtr<HtmlVisitor2> htmlVisitor(new HtmlVisitor2());
///browser->GetMainFrame()->GetSource(htmlVisitor);
//client->getbrowser
//browser->GetHost()->CloseBrowser(true);
}

int main(int argc, char* argv[]) {
    CefMainArgs mainArgs{};
    CefRefPtr<CefApp> app{};

    // SimpleHandler implements browser-level callbacks.
    // CefRefPtr<SimpleHandler> handler(new SimpleHandler(false));
    void* sandbox_info = nullptr;

    auto exitCode = CefExecuteProcess(mainArgs, nullptr, sandbox_info);
    if(exitCode >= 0) {
        // The sub-process has completed so return here.
        return exitCode;
    }

    CefSettings settings;
    settings.no_sandbox = true;
    settings.windowless_rendering_enabled = true;

    // CefRefPtr<SimpleApp> app(sap);
    CefInitialize(mainArgs, settings, app.get(), sandbox_info);

    std::vector<std::string> urls = { "https://www.aliexpress.com/all-wholesale-products.html" };

    std::vector<std::thread> threads;
    for(const auto& url : urls) {
        threads.emplace_back(std::thread(RunBrowser, url));
    }

    for(auto& t : threads) {
        t.join();
    }

    CefRunMessageLoop();
    CefShutdown();

    return 0;
}