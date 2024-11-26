/*
III. Error Handling Matrix


Reception Error Cases:
┌─────────────────┬────────────────┬─────────────────┐
│ Condition       │ Action         │ Return          │
├─────────────────┼────────────────┼─────────────────┤
│ read() error    │ Clean memory   │ NULL            │
│ malloc() fails  │ Clean memory   │ NULL            │
│ join() fails    │ Clean memory   │ NULL            │
└─────────────────┴────────────────┴─────────────────┘

Memory Management:
┌─────────────────┬────────────────┐
│ Operation       │ Cleanup        │
├─────────────────┼────────────────┤
│ New allocation  │ Free old       │
│ Error condition │ Free all       │
│ EOF reached     │ Free temp      │
└─────────────────┴────────────────┘

*/
