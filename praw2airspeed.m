function [airspeed_ms] = praw2airspeed(p_raw_decimal)
    PMAX_PSI = 1;
    PMIN_PSI = -1;
    AIR_DENSITY = 1.225;
    for n = 1 : length(p_raw_decimal)
        p_psi = (((p_raw_decimal(n)-819.15)*(PMAX_PSI-PMIN_PSI))/14744.7)+PMIN_PSI;
        if(p_psi >= 0)
            airspeed_ms(n) = sqrt((2*6894.7*p_psi)/AIR_DENSITY);
        else
            airspeed_ms(n) = -sqrt((2*6894.7*abs(p_psi))/AIR_DENSITY);
        end
    end
    airspeed_ms = airspeed_ms';
end

