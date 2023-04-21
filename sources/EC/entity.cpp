#include <EC/entity.h>
#include <EC/component.h>

namespace magma_engine
{
	namespace ec {

		Entity::~Entity() {
			for (auto c : cmps)
				if (c != nullptr)
					delete c;
		}

		bool Entity::init(ec::grpId_type gId_)
		{
			gId = gId_;
			currCmps.reserve(ec::maxComponentId);

			return true;
		}

		void Entity::setContext(EntityManager* mngr_)
		{
			mngr = mngr_;
		}

		void Entity::setAlive(bool alive_)
		{
			alive = alive_;
		}

		void Entity::update(float deltaTime) {
			auto n = currCmps.size();
			for (auto i = 0u; i < n; i++)
				currCmps[i]->update(deltaTime);
		}

		void Entity::render() {
			auto n = currCmps.size();
			for (auto i = 0u; i < n; i++)
				currCmps[i]->render();
		}

		// por ahora no tenemos flush de mensajes implementado, dejar elay a false
		void Entity::send(const Message& m, bool delay) {
			if (!delay) {
				for (Component* c : cmps) {
					if (c != nullptr)
						c->recieve(m);
				}
			}
			else {
				msgs_.emplace_back(m);
			}
		}

		//void Entity::flushMessages(){

		//	// we traverse until msgs_.size(), so if new message
		//	// we added we don't send them now. If you wish to send
		//	// them as will you should write this loop in a different way
		//	// and maybe using std::list would be better.

		//	auto size = msgs_.size();
		//	for (auto i = 0u; i < size; i++) {
		//		auto& m = msgs_[i];
		//		for (Component* c : cmps) {
		//			if (c != nullptr)
		//				c->recieve(m);
		//		}
		//	}

		//	// delete all message that we have sent. This might be expensive
		//	// since it has to shift all remaining elements to the left. A better
		//	// solution would be to keep two vectors 'v1' and 'v2', when sending a
		//	// message we always add it to 'v1' and in flush we swap them and send
		//	// all messages in v2. After flush we simply clear v2
		//	
		//	msgs_.erase(msgs_.begin(), msgs_.begin() + size);
		//}
	}
}

