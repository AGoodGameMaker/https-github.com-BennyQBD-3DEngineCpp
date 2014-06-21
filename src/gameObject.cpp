/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gameObject.h"
#include "gameComponent.h"
#include "coreEngine.h"

GameObject::~GameObject()
{
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		if(m_components[i])
		{	
			delete m_components[i];
		}
	}
	
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		if(m_children[i]) 
		{
			delete m_children[i];
		}
	}
}

GameObject* GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child); 
	child->GetTransform()->SetParent(&m_transform);
	child->SetEngine(m_coreEngine);
	return this;
}

GameObject* GameObject::AddComponent(GameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void GameObject::ProcessInputAll(const Input& input, float delta)
{
	ProcessInput(input, delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->ProcessInputAll(input, delta);
	}
}

void GameObject::UpdateAll(float delta)
{
	Update(delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->UpdateAll(delta);
	}
}

void GameObject::RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	Render(shader, renderingEngine, camera);

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->RenderAll(shader, renderingEngine, camera);
	}
}

void GameObject::ProcessInput(const Input& input, float delta)
{
	m_transform.Update();

	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->ProcessInput(input, delta);
	}
}

void GameObject::Update(float delta)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Update(delta);
	}
}

void GameObject::Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Render(shader, renderingEngine, camera);
	}
}

void GameObject::SetEngine(CoreEngine* engine)
{
	if(m_coreEngine != engine)
	{
		m_coreEngine = engine;
		
		for(unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->AddToEngine(engine);
		}

		for(unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetEngine(engine);
		}
	}
}

std::vector<GameObject*> GameObject::GetAllAttached()
{
	std::vector<GameObject*> result;
	
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		std::vector<GameObject*> childObjects = m_children[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}
	
	result.push_back(this);
	return result;
}
