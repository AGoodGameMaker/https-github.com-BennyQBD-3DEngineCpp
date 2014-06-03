#include "3DEngine.h"
#include "freeLook.h"
#include "freeMove.h"

class TestGame : public Game
{
public:
	TestGame() {}
	
	virtual void Init(const Window& window);
protected:
private:
	TestGame(const TestGame& other) {}
	void operator=(const TestGame& other) {}
};

void TestGame::Init(const Window& window)
{
	Material bricks("bricks", Texture("bricks.jpg"), 0.5f, 4, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
	Material bricks2("bricks2", Texture("bricks2.jpg"), 1, 8, Texture("bricks2_normal.png"), Texture("bricks2_disp.jpg"), 0.04f, -1.0f);
	
	AddToScene((new GameObject(Vector3f(0, -1, 5), Quaternion(), 4.0f))
		->AddComponent(new MeshRenderer(Mesh("./res/models/plane4.obj"), Material("bricks"))));
	AddToScene((new GameObject(Vector3f(7,0,7)))
		->AddComponent(new PointLight(Vector3f(0,1,0),0.4f,Attenuation(0,0,1))));
	
	AddToScene((new GameObject(Vector3f(10,1.0f,5), Quaternion(Vector3f(1,0,0), ToRadians(-60.0f)) * Quaternion(Vector3f(0,1,0), ToRadians(90.0f))))
		->AddComponent(new SpotLight(Vector3f(0,1,1),0.4f,Attenuation(0,0,0.02f),ToRadians(91.1f), 7, 1.0f, 0.5f)));
	
	AddToScene((new GameObject(Vector3f(), Quaternion(Vector3f(1,0,0), ToRadians(-45))))
		->AddComponent(new DirectionalLight(Vector3f(1,1,1), 0.4f, 10, 80.0f, 1.0f)));
	
	AddToScene((new GameObject(Vector3f(0, 2, 0), Quaternion(Vector3f(0,1,0), 0.4f), 1.0f))
		->AddComponent(new MeshRenderer(Mesh("./res/models/plane3.obj"),Material("bricks2")))
		->AddChild((new GameObject(Vector3f(0, 0, 25)))
			->AddComponent(new MeshRenderer(Mesh("./res/models/plane3.obj"),Material("bricks2")))
			->AddChild((new GameObject())
				->AddComponent(new Camera(Matrix4f().InitPerspective(ToRadians(70.0f), window.GetAspect(), 0.1f, 1000.0f)))
				->AddComponent(new FreeLook(window.GetCenter()))
				->AddComponent(new FreeMove()))));
	
	AddToScene((new GameObject(Vector3f(14,0,5), Quaternion(Vector3f(0,1,0), ToRadians(30.0f))))
		->AddComponent(new MeshRenderer(Mesh("./res/models/cube.obj"), Material("bricks2"))));
}

int main()
{
	TestGame game;
	CoreEngine engine(800, 600, 60, &game);
	engine.CreateWindow("3D Game Engine");
	engine.Start();
	
	return 0;
}