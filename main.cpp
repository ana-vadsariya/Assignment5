"Ride base class"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> newWith: id pickup: pickup dropoff: drop distance: dist [
        | instance |
        instance := self new.
        instance initWith: id pickup: pickup dropoff: drop distance: dist.
        ^ instance
    ]

    initWith: id pickup: pickup dropoff: drop distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := drop.
        distance := dist.
    ]

    fare [
        self subclassResponsibility
    ]

    rideDetails [
        ('Ride ID: ', rideID printString, ' | From: ', pickupLocation,
         ' | To: ', dropoffLocation, ' | Distance: ', distance printString, ' miles') displayNl.
    ]
]

"StandardRide subclass"
Ride subclass: StandardRide [
    fare [
        ^ distance * 1.5
    ]
]

"PremiumRide subclass"
Ride subclass: PremiumRide [
    fare [
        ^ distance * 3.0
    ]
]

"Driver class"
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> newWith: id name: n rating: r [
        | instance |
        instance := self new.
        instance initWith: id name: n rating: r.
        ^ instance
    ]

    initWith: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := OrderedCollection new.
    ]

    addRide: r [
        assignedRides add: r.
    ]

    getDriverInfo [
        ('Driver ID: ', driverID printString, ', Name: ', name,
         ', Rating: ', rating printString, ', Rides Completed: ',
         assignedRides size printString) displayNl.
    ]
]

"Rider class"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> newWith: id name: n [
        | instance |
        instance := self new.
        instance initWith: id name: n.
        ^ instance
    ]

    initWith: id name: n [
        riderID := id.
        name := n.
        requestedRides := OrderedCollection new.
    ]

    requestRide: r [
        requestedRides add: r.
    ]

    viewRides [
        ('Rider ID: ', riderID printString, ', Name: ', name, '''s Ride History:') displayNl.
        requestedRides do: [:ride |
            ride rideDetails.
            ('Fare: $', ride fare printString) displayNl.
        ].
    ]
]

"==== MAIN DEMO ===="
| ride1 ride2 rides driver1 rider1 |

ride1 := StandardRide newWith: 1001 pickup: 'Station' dropoff: 'Airport' distance: 10.0.
ride2 := PremiumRide newWith: 1002 pickup: 'Mall' dropoff: 'Hotel' distance: 5.0.

rides := OrderedCollection with: ride1 with: ride2.

driver1 := Driver newWith: 1 name: 'Ana' rating: 4.7.
driver1 addRide: ride1.
driver1 addRide: ride2.

rider1 := Rider newWith: 1 name: 'Sihan'.
rider1 requestRide: ride1.
rider1 requestRide: ride2.

'=== Driver Info ===' displayNl.
driver1 getDriverInfo.

'=== Rider Ride History ===' displayNl.
rider1 viewRides.

'=== All Rides (Polymorphism Demo) ===' displayNl.
rides do: [:r |
    r rideDetails.
    ('Fare: $', r fare printString) displayNl.
].
