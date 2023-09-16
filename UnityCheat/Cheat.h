WeaponView* weaponView;
BobEffect* bobEffect;
Character* character;

auto Hooks::AddRecoil(float camRecoil, float gunRecoil, float recoilRecover) -> void
{
    __try {
        camRecoil = 0.f;
        gunRecoil = 0.f;
        recoilRecover = 100.f;
    }
    __except (true) {
        printf("AddRecoil!");
    }
}

auto Hooks::CalculateSpread() -> float
{
    __try {
        if (GetAsyncKeyState(VK_END) & 1) {
            Hooks::UnHook();
        }

        return 0.f;
    }
    __except (true) {
        printf("CalculateSpread!");
    }
}
auto Hooks::CalculateSpreadPenalty() -> float
{
    __try {
        return 0.f;
    }
    __except (true) {
        printf("CalculateSpreadPenalty!");
    }
}

/*auto Hooks::GravityMultiplier(float speedY, bool crouching)-> float
{
    __try {
        speedY = 100.f;
        crouching = false;
        return Hooks::GravityMultiplierhk.get_original< decltype(&GravityMultiplier)>()(speedY, crouching);
    }
    __except (true) {
        printf("GravityMultiplier!");
    }
}*/