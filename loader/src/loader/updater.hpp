﻿#pragma once

#include <string>
#include <Geode/utils/MiniFunction.hpp>
#include <Geode/loader/Index.hpp>

namespace geode::updater {
    struct ResourceDownloadEvent : public Event {
        const UpdateStatus status;
        explicit ResourceDownloadEvent(UpdateStatus status);
    };

    class ResourceDownloadFilter : public EventFilter<ResourceDownloadEvent> {
    public:
        using Callback = void(ResourceDownloadEvent*);

        static ListenerResult handle(const utils::MiniFunction<Callback>& fn, ResourceDownloadEvent* event);
        ResourceDownloadFilter();
    };

    struct LoaderUpdateEvent : public Event {
        const UpdateStatus status;
        explicit LoaderUpdateEvent(UpdateStatus status);
    };

    class LoaderUpdateFilter : public EventFilter<LoaderUpdateEvent> {
    public:
        using Callback = void(LoaderUpdateEvent*);

        static ListenerResult handle(const utils::MiniFunction<Callback>& fn, LoaderUpdateEvent* event);
        LoaderUpdateFilter();
    };

    void updateSpecialFiles();
    void tryDownloadLoaderResources(std::string const& url, bool tryLatestOnError = true);
    void downloadLoaderResources(bool useLatestRelease = false);
    void downloadLoaderUpdate(std::string const& url);
    void fetchLatestGithubRelease(
        const utils::MiniFunction<void(matjson::Value const&)>& then,
        utils::MiniFunction<void(std::string const&)> expect
    );

    bool verifyLoaderResources();
    void checkForLoaderUpdates();
    bool isNewUpdateDownloaded();
}
