function [airspeed_ms] = bertz2airspeed(bertz)
    for n = 1 : length(bertz)
        airspeed_ms(n) = 4.03*sqrt(bertz(n));
    end
    airspeed_ms = airspeed_ms';
end