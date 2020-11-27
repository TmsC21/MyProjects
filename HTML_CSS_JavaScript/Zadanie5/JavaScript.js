var map;
var markers = [];
var directionsService;
var directionsRenderer;
var uluru = { lat: 48.1518966, lng: 17.073141 };
const iconBase = "http://maps.google.com/mapfiles/kml/shapes/";
const icons = {
    skola: {
        icon: iconBase + "ranger_station.png",
    },
    zastavka: {
        icon: iconBase + "bus.png",
    },
    zastavka_el: {
        icon: iconBase + "tram.png",
    },
};
function initMap() {
    // The map, centered at Uluru
    map = new google.maps.Map(document.getElementById("map"), {
        zoom: 17,
        center: uluru,
    });
    const panorama = new google.maps.StreetViewPanorama(
        document.getElementById("pano"),
        {
            position: uluru,
            pov: {
                heading: 34,
                pitch: 10,
            },
        }
    );
    map.setStreetView(panorama);

    directionsService = new google.maps.DirectionsService();
    directionsRenderer = new google.maps.DirectionsRenderer();
    directionsRenderer.setMap(map);

    // The marker, positioned at Uluru
    const marker = new google.maps.Marker({
        position: uluru,
        map: map,
        icon: icons.skola.icon,
        content:"Fakulta elektrotechniky a informatiky Slovenskej technickej univerzity v Bratislave lat: 48.1518966, lng: 17.073141",
    });

    if(marker.content) {
        var infoWindow = new google.maps.InfoWindow({
            content: marker.content
        });
    }
    marker.addListener('click', function(){
        infoWindow.open(map, marker);
    });
    initAutocomplete();
}
let zobraz = 1;
let markerss =[];
function zobrazZastavky(){
    if(zobraz === 1){
        zobraz = 0;
    }else{
        zobraz = 1;
    }
    const features = [
        {
            position: new google.maps.LatLng(48.154123, 17.075112),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.154635, 17.074403),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.154610, 17.075725),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.154119, 17.076871),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.156007, 17.072022),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.156294, 17.071650),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.148242, 17.071895),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.147920, 17.072485),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.154478, 17.065077),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.156424, 17.064287),
            type: "zastavka",
        },
        {
            position: new google.maps.LatLng(48.148088, 17.071694),
            type: "zastavka_el",
        },
        {
            position: new google.maps.LatLng(48.148197, 17.072397),
            type: "zastavka_el",
        }];
        if(zobraz === 0){
            for (let i = 0; i < features.length; i++) {
                const marker = new google.maps.Marker({
                    position: features[i].position,
                    icon: icons[features[i].type].icon,
                    map: map,
                });
                markerss.push(marker);
            }
            document.getElementById("zastavky").innerText = "Zruš zastávky";
        }
        else{
            document.getElementById("zastavky").innerText = "Zobraz zastávky";
            for (let i = 0; i < features.length; i++) {
                markerss[i].setMap(null);
            }
            markerss = [];
        }

}
function initAutocomplete() {
    // Create the search box and link it to the UI element.
    const input = document.getElementById("inputPlace");
    const searchBox = new google.maps.places.SearchBox(input);
    // Bias the SearchBox results towards current map's viewport.
    map.addListener("bounds_changed", () => {
        searchBox.setBounds(map.getBounds());
    });

    // Listen for the event fired when the user selects a prediction and retrieve
    // more details for that place.
    searchBox.addListener("places_changed", () => {
        const places = searchBox.getPlaces();
        if (places.length == 0) {
            return;
        }
        // Clear out the old markers.
        markers.forEach((marker) => {
            marker.setMap(null);
        });
        markers = [];
        // For each place, get the icon, name and location.
        const bounds = new google.maps.LatLngBounds();
        places.forEach((place) => {
            if (!place.geometry) {
                console.log("Returned place contains no geometry");
                return;
            }
            const icon = {
                url: place.icon,
                size: new google.maps.Size(71, 71),
                origin: new google.maps.Point(0, 0),
                anchor: new google.maps.Point(17, 34),
                scaledSize: new google.maps.Size(25, 25),
            };
            // Create a marker for each place.
            markers.push(
                new google.maps.Marker({
                    map,
                    icon,
                    title: place.name,
                    position: place.geometry.location,
                })
            );

            if (place.geometry.viewport) {
                // Only geocodes have viewport.
                bounds.union(place.geometry.viewport);
            } else {
                bounds.extend(place.geometry.location);
            }
        });
        map.fitBounds(bounds);
    });
}
function travel(){
    let peso = document.getElementById("chodza").checked;
    if(peso === true){
        return 'WALKING';
    }
    else{
        return 'DRIVING';
    }
}
function vypocetRoute(){
    calculateAndDisplayRoute(directionsService, directionsRenderer);
    var service = new google.maps.DistanceMatrixService();
    const route = {
        origin: uluru,
        destination: markers[0].position,
        travelMode: travel(),
    }
    directionsService.route(route,
        function(response, status) { // anonymous function to capture directions
            if (status !== 'OK') {
                window.alert('Directions request failed due to ' + status);
                return;
            } else {
                directionsRenderer.setDirections(response); // Add route to the map
                var directionsData = response.routes[0].legs[0]; // Get data about the mapped route
                if (!directionsData) {
                    window.alert('Directions request failed');
                    return;
                }
                else {
                    if(travel() === 'DRIVING'){
                        document.getElementById('output').innerHTML = " Autom je to " + directionsData.distance.text + " (" + directionsData.duration.text + ").";
                    }
                    else{
                        document.getElementById('output').innerHTML = " Pešo je to " + directionsData.distance.text + " (" + directionsData.duration.text + ").";
                    }
                }
            }
        });
}
function calculateAndDisplayRoute(directionsService, directionsRenderer) {
    directionsService.route(
        {
            origin: uluru,
            destination: markers[0].position,
            travelMode: travel(),
        },
        (response, status) => {
            if (status === "OK") {
                directionsRenderer.setDirections(response);
            } else {
                window.alert("Directions request failed due to " + status);
            }
        }
    );
}