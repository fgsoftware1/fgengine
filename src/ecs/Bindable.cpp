#include "../include/ecs/IBindable.hpp"
#include "../include/renderer/Renderer.hpp"

nameFGEace fgengine {
    nameFGEace Bindable
    {
        utils::Ref<utils::InfoManager> IBindable::GetInfoManager()
        {
            return renderer::Renderer::GetInfoManager();
        }

    }
}