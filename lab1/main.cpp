#include <iostream>
#include <algorithm>

#include "FlatMap.h"
#include <gtest/gtest.h>

typedef std::string Key;

TEST(FlatMapTest, constructors) {
    FlatMap m1;
    ASSERT_TRUE(m1.empty());

    FlatMap m2(m1);
    ASSERT_TRUE(m1.empty());
    ASSERT_TRUE(m2.empty());

    m2.insert("Stanley", {19, 74});
    FlatMap m3(m2);
    ASSERT_EQ(m2.size(), 1);
    ASSERT_EQ(m3.size(), 1);
    ASSERT_TRUE(m3.contains("Stanley"));
    ASSERT_TRUE(m2.contains("Stanley"));

    FlatMap m4(std::move(m3));
    ASSERT_EQ(m4.size(), 1);
    ASSERT_TRUE(m4.contains("Stanley"));
    ASSERT_TRUE(m3.empty());
    ASSERT_TRUE(m2.contains("Stanley"));
}

TEST(FlatMaptest, swap) {
    FlatMap m1;
    FlatMap m2;
    m2.insert("Bob", {12, 29});
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m1.empty());
    ASSERT_FALSE(m2.empty());
    ASSERT_TRUE(m2.contains("Bob"));

    m1.swap(m2);
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m2.empty());
    ASSERT_FALSE(m1.empty());
    ASSERT_FALSE(m2.contains("Bob"));
}

TEST(FlatMaptest, assignment) {
    FlatMap m1;
    m1.insert("Shrek", {35, 160});
    FlatMap m2;
    m2.insert("Fiona", {27, 100});
    ASSERT_TRUE(m1.contains("Shrek"));
    ASSERT_TRUE(m2.contains("Fiona"));
    ASSERT_FALSE(m1.contains("Fiona"));

    m1 = m2;
    ASSERT_FALSE(m1.contains("Shrek"));
    ASSERT_TRUE(m2.contains("Fiona"));
    ASSERT_TRUE(m1.contains("Fiona"));

    m2 = std::move(m1);
    ASSERT_TRUE(m2.contains("Fiona"));
    ASSERT_TRUE(m1.empty());

    FlatMap m3, m4;
    m3 = m4 = m2;
    ASSERT_EQ(m2, m3);
    ASSERT_EQ(m3, m4);

    m2 = m3 = std::move(m4);
    ASSERT_EQ(m2, m3);
    ASSERT_TRUE(m4.empty());
}

TEST(FlatMaptest, cleanse) {
    FlatMap m1;
    m1.insert("Alex", {38, 59});
    m1.insert("Sarah", {64, 82});
    m1.insert("Ginny", {20, 46});
    ASSERT_EQ(m1.size(), 3);
    m1.clear();
    ASSERT_TRUE(m1.empty());
}

TEST(FlatMaptest, erasing) {
    FlatMap m;
    m.insert("Braxton", {33, 79});
    m.insert("Jackson", {38, 59});
    m.insert("Milo", {45, 61});
    m.insert("Philip", {23, 78});
    m.insert("Remington", {18, 75});

    FlatMap m2 = m;

    ASSERT_EQ(m.size(), 5);

    ASSERT_TRUE(m.erase("Braxton"));                //удалим первого
    ASSERT_EQ(m.size(), 4);
    ASSERT_FALSE(m.contains("Braxton"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Remington");

    ASSERT_TRUE(m.erase("Remington"));              //удалим последнего
    ASSERT_EQ(m.size(), 3);
    ASSERT_FALSE(m.contains("Remington"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Philip");

    ASSERT_TRUE(m.erase("Milo"));                   //удалим некрайнего
    ASSERT_EQ(m.size(), 2);
    ASSERT_FALSE(m.contains("Milo"));
    ASSERT_EQ(m.firstKey(), "Jackson");
    ASSERT_EQ(m.lastKey(), "Philip");

    ASSERT_FALSE(m.erase("Marigold"));
    ASSERT_FALSE(m.contains("Marigold"));
    ASSERT_EQ(m.size(), 2);

    ASSERT_TRUE(m2.erase("Remington"));
    ASSERT_TRUE(m2.erase("Braxton"));
    ASSERT_TRUE(m2.erase("Milo"));

    ASSERT_TRUE(m == m2);                               //не зависит от порядка удаления

    FlatMap m3;
    ASSERT_TRUE(m3.empty());
    ASSERT_FALSE(m3.erase("Remington"));
}

TEST(FlatMaptest, inserting) {
    FlatMap m;
    ASSERT_TRUE(m.insert("Ember", {27, 73}));
    ASSERT_EQ(m.firstKey(), "Ember");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 1);

    ASSERT_TRUE(m.insert("Dolores", {82, 60}));
    ASSERT_EQ(m.firstKey(), "Dolores");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 2);

    ASSERT_TRUE(m.insert("Aredhel Ar-Feiniel", {538, 40}));
    ASSERT_EQ(m.firstKey(), "Aredhel Ar-Feiniel");
    ASSERT_EQ(m.lastKey(), "Ember");
    ASSERT_EQ(m.size(), 3);

    ASSERT_TRUE(m.insert("Temperance", {40, 71}));
    ASSERT_EQ(m.firstKey(), "Aredhel Ar-Feiniel");
    ASSERT_EQ(m.lastKey(), "Temperance");
    ASSERT_EQ(m.size(), 4);

    ASSERT_FALSE(m.insert("Ember", {29, 80}));
    ASSERT_EQ(m.size(), 4);

    FlatMap m2;
    ASSERT_TRUE(m2.insert("Aredhel Ar-Feiniel", {538, 40}));
    ASSERT_TRUE(m2.insert("Temperance", {40, 71}));
    ASSERT_TRUE(m2.insert("Ember", {27, 73}));
    ASSERT_TRUE(m2.insert("Dolores", {82, 60}));

    ASSERT_TRUE(m == m2);
}

TEST(FlatMaptests, resize) {
    FlatMap m;
    ASSERT_TRUE(m.insert("James", {30, 75}));                       //здесь выделится память
    ASSERT_TRUE(m.insert("Oliver", {35, 80}));                      //и вот здесь
    ASSERT_TRUE(m.insert("Sophie", {40, 70}));
    ASSERT_TRUE(m.insert("Michael", {53, 92}));                     //и вот тут
    ASSERT_TRUE(m.insert("Emma",  {27, 62}));
    ASSERT_TRUE(m.insert("Isabella", {29, 64}));
    ASSERT_TRUE(m.insert("George", {18, 70}));
    ASSERT_TRUE(m.insert("Gabriella", {33, 66}));                   //а еще здесь
    ASSERT_TRUE(m.insert("William", {42, 85}));

    ASSERT_EQ(m.size(), 9);

    m.clear();

    ASSERT_TRUE(m.insert("James", {30, 75}));
    ASSERT_TRUE(m.insert("Oliver", {35, 80}));
    ASSERT_TRUE(m.insert("Sophie", {40, 70}));
    ASSERT_TRUE(m.insert("Michael", {53, 92}));
    ASSERT_TRUE(m.insert("Emma",  {27, 62}));
    ASSERT_TRUE(m.insert("Isabella", {29, 64}));
    ASSERT_TRUE(m.insert("George", {18, 70}));
    ASSERT_TRUE(m.insert("Gabriella", {33, 66}));
    ASSERT_TRUE(m.insert("William", {42, 85}));

    ASSERT_EQ(m.size(), 9);
}

TEST(FlatMaptests, access) {
    FlatMap m1;

    m1.insert("Willow", {52, 80});
    m1.insert("Harrison", {34, 92});
    m1.insert("Edward", {3, 14});
    m1.insert("Jemma", {14, 38});
    m1.insert("Archie", {71, 102});

    FlatMap m2 = m1;
    const FlatMap m3 = m1;

    ASSERT_EQ(m1["Willow"].age, 52);
    ASSERT_EQ(m1["Willow"].weight, 80);
    ASSERT_EQ(m1["Archie"].age, 71);
    ASSERT_EQ(m1["Archie"].weight, 102);

    ASSERT_TRUE(m1.erase("Jemma"));
    ASSERT_FALSE(m1.contains("Jemma"));
    EXPECT_NO_THROW(m1["Jemma"]);
    ASSERT_EQ(m1["Jemma"].age, Value().age);
    ASSERT_EQ(m1["Jemma"].weight, Value().weight);
    ASSERT_TRUE(m1.contains("Jemma"));
    ASSERT_FALSE(m1.insert("Jemma", {14, 38}));

    ASSERT_EQ(m2.at("Willow").age, 52);
    ASSERT_EQ(m2.at("Willow").weight, 80);
    ASSERT_EQ(m2.at("Archie").age, 71);
    ASSERT_EQ(m2.at("Archie").weight, 102);

    m2.erase("Jemma");
    EXPECT_ANY_THROW(m2.at("Jemma"));
    ASSERT_THROW(m2.at("Jemma"), std::out_of_range);

    ASSERT_EQ(m3.at("Willow").age, 52);
    ASSERT_EQ(m3.at("Willow").weight, 80);
    ASSERT_EQ(m3.at("Archie").age, 71);
    ASSERT_EQ(m3.at("Archie").weight, 102);

    EXPECT_ANY_THROW(m3.at("Andrew"));
    ASSERT_THROW(m3.at("Andrew"), std::out_of_range);
}

TEST(FlatMaptest, comparison) {
    FlatMap m1;

    m1.insert("Willow", {52, 80});
    m1.insert("Harrison", {34, 92});
    m1.insert("Edward", {3, 14});
    m1.insert("Jemma", {14, 38});
    m1.insert("Archie", {71, 102});

    ASSERT_TRUE(m1 == m1);
    ASSERT_FALSE(m1 != m1);

    FlatMap m2 = m1;
    m2.erase("Archie");
    ASSERT_LE(m2.size(), m1.size());
    ASSERT_TRUE(m1 != m2);
    ASSERT_FALSE(m1 == m2);

    FlatMap m3 = m2;
    m3.insert("Alister", {71, 102});
    ASSERT_EQ(m1.size(), m3.size());
    ASSERT_TRUE(m1 != m3);                                  //несовпадение ключа
    ASSERT_FALSE(m1 == m3);

    FlatMap m4 = m2;
    m4.insert("Archie", {13, 52});
    ASSERT_EQ(m1.size(), m4.size());
    ASSERT_NE(m1["Archie"].age, m4["Archie"].age);          //несовпадение значения
    ASSERT_NE(m1["Archie"].weight, m4["Archie"].weight);
    ASSERT_TRUE(m1 != m4);
    ASSERT_FALSE(m1 == m4);

    FlatMap m5 = m2;
    m5.insert("Archie", {71, 105});
    ASSERT_EQ(m1.size(), m4.size());
    ASSERT_EQ(m1["Archie"].age, m5["Archie"].age);           //несовпадение одного поля
    ASSERT_NE(m1["Archie"].weight, m5["Archie"].weight);
    ASSERT_TRUE(m1 != m5);
    ASSERT_FALSE(m1 == m5);
}

TEST(FlatMapTest, sizeAndEmpty) {
    FlatMap m;

    ASSERT_TRUE(m.empty());
    ASSERT_EQ(m.size(), 0);

    m.insert("Nathan", {40, 92});
    ASSERT_FALSE(m.empty());
    ASSERT_EQ(m.size(), 1);

    m.insert("Simon", {14, 49});
    ASSERT_FALSE(m.empty());
    ASSERT_EQ(m.size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}