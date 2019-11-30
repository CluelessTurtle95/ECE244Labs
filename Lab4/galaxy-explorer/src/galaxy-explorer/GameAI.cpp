#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>

GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

static int aimSetID = -1;



SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);

	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		}
	}
        
        AsteroidsObserver asteroidObs = asteroidsObserver();
        if(asteroidObs.asteroids().isEmpty())
        {
            return SuggestedAction{ (-ship_state.millidegree_rotation > 0) ? SuggestedAction::YawingClockwise : SuggestedAction::YawingAntiClockwise , SuggestedAction::FiringNo };
        }
        else
        {
            float hitangle;
            int z;
            float f;
            if(aimSetID == -1)
            {
                sf::IntRect hit = asteroidObs.asteroids().front().getCurrentHitbox();
                sf::IntRect ship = ship_state.hitbox;
                hitangle = (float)(hit.left-ship.left)/(ship.top - hit.top);
                hitangle = 180000 * std::atan(hitangle) / 3.14 ;
                
                z = hitangle - ship_state.millidegree_rotation;
                z = abs(z) % 360000;
                std::cout << z << " ";
                
                if( z < 100)
                {
                    return SimpleActions::STOP_YAWING_AND_FIRE;
                }
                sf::RectangleShape line;
                sf::RectangleShape line2;
                line.setPosition(sf::Vector2f(ship.left,ship.top));
                line2.setPosition(sf::Vector2f(ship.left,ship.top));
                line2.setRotation(ship_state.millidegree_rotation/1000 - 90);
                line2.setFillColor(sf::Color::Red);
                line.setRotation(hitangle/1000 - 90);
                
                line.setSize(sf::Vector2f(4000,40));
                line2.setSize(sf::Vector2f(4000,40));
                debug_rt->draw(line);
                debug_rt->draw(line2);
            }
        }
        //std::cout << ship_state.millidegree_rotation << " ";
	//return SimpleActions::NO_CHANGE;
	return SimpleActions::START_YAWING_CW;
	// return SimpleActions::START_YAWING_ACW;
	//return SimpleActions::STOP_YAWING_AND_FIRE;
	
}
