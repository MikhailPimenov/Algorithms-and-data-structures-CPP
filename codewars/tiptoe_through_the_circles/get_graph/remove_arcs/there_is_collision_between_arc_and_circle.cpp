#include "there_is_collision_between_arc_and_circle.h"


bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle) {

    const double distance = get_distance(arc.m_owner->m_center, circle.m_center);
    
    if (distance > arc.m_owner->m_radius + circle.m_radius ||
        arc.m_owner->m_radius > distance + circle.m_radius)
        return false;

    const double angle = get_angle_with_x_axis(circle.m_center, arc.m_owner->m_center);
    const double angle_a = get_angle_with_x_axis(arc.m_a, arc.m_owner->m_center);
    const double angle_b = get_angle_with_x_axis(arc.m_b, arc.m_owner->m_center);
  
    const double delta_angle = angle_a > angle_b ? 
        angle_a - angle_b : 2.0 * g_pi + angle_a - angle_b;

    if (is_between(angle, angle_a, angle_a - delta_angle))
        return true;

    if (get_distance(arc.m_a, circle.m_center) > circle.m_radius &&
        get_distance(arc.m_b, circle.m_center) > circle.m_radius)
        return false;

    return true;
}